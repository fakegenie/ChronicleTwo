#!/usr/bin/env python3
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools" / "mwccgap"))

from mwccgap.constants import FUNCTION_PREFIX, SYMBOL_AT, SYMBOL_DOLLAR  # noqa: E402
from mwccgap.elf import Elf, Relocation, Symbol  # noqa: E402
from mwccgap.mwccgap import replace_sinit  # noqa: E402
from mwccgap.preprocessor import Preprocessor  # noqa: E402

REGION = os.environ.get("REGION", "PAL").lower()
UNITS = ROOT / "ps2" / "config" / REGION / "state_units.txt"
PRIMERS = ROOT / "ps2" / "config" / REGION / "primers"
ASM_MARKER = re.compile(r'INCLUDE_ASM\("[^"]*",\s*([^)\s]+)\)')
ANONYMOUS = re.compile(r"(@|.+\$)(\d+)")
STT_SECTION = 3
STB_GLOBAL = 1
SHT_NOBITS = 8
STT_FUNC = 2


def state_units():
    if not UNITS.is_file():
        return {}
    units = {}
    for line in UNITS.read_text().splitlines():
        words = line.split()
        if not words:
            continue
        options = {"drafts": "drafts" in words[1:], "primer": None}
        for word in words[1:]:
            if word.startswith("primer="):
                options["primer"] = word[len("primer="):]
            elif word != "drafts":
                raise ValueError(f"{UNITS.name}: {words[0]}: unknown option {word}")
        units[words[0]] = options
    return units


def unit_options(unit):
    return state_units().get(unit)


def primer_text(options):
    if not options or not options["primer"]:
        return ""
    return (PRIMERS / f"{options['primer']}.cpp").read_text()


def prepare(text, options, all_drafts=False):
    if not options:
        return text, []
    drafts = []
    if options["drafts"] and not all_drafts:
        text, drafts = enable_drafts(text)
    return primer_text(options) + text, drafts


def enable_drafts(text):
    lines = text.split("\n")
    stack = []
    drafts = []
    for index, line in enumerate(lines):
        directive = line.strip()
        if directive.startswith("#if"):
            stack.append({"head": directive, "line": index, "else": None})
        elif directive.startswith("#else") and stack:
            stack[-1]["else"] = index
        elif directive.startswith("#endif") and stack:
            block = stack.pop()
            if block["head"] != "#ifdef NONMATCHING" or block["else"] is None:
                continue
            other = [entry.strip() for entry in lines[block["else"] + 1:index] if entry.strip()]
            markers = [ASM_MARKER.match(entry) for entry in other]
            if other and all(markers):
                lines[block["line"]] = "#if 1"
                drafts.extend(marker.group(1) for marker in markers)
    return "\n".join(lines), drafts


def expand(text):
    lines, asm_files = Preprocessor().preprocess_c_file(text.splitlines(True))
    return "\n".join(lines), [path.stem for path, count in asm_files]


def state_source(text, options):
    prepared, drafts = prepare(text, options)
    expanded, markers = expand(prepared)
    return expanded, drafts, markers


def unit_of(source):
    path = Path(source).resolve()
    base = ROOT / "ps2" / "src"
    if base in path.parents:
        return path.relative_to(base).with_suffix("").as_posix()
    return path.stem


def compile_text(text, source, flags):
    mwcc = Path(os.environ.get("MW_DIR", "tools/compilers/mw/3.0-011126")) / "mwccps2.exe"
    flags = [flag for flag in flags if flag not in ("-MD", "-gccdep")] + ["-DSTATEMATCHING"]
    with tempfile.NamedTemporaryFile(suffix=".c", dir=Path(source).parent) as temp, \
            tempfile.TemporaryDirectory() as out:
        temp.write(text.encode())
        temp.flush()
        output = Path(out) / "state.o"
        command = ["wibo", str(mwcc), "-c", *flags, "-o", str(output), temp.name]
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                stdin=subprocess.DEVNULL, text=True)
        if result.stdout.strip():
            sys.stderr.write(result.stdout.replace("\r", ""))
        if result.returncode or not output.is_file():
            raise ValueError(f"{source}: state compile failed")
        elf = Elf(output.read_bytes())
        temp_name = Path(temp.name).name
    for symbol in elf.symtab.symbols:
        if "__sinit_" + temp_name in symbol.name:
            symbol.name = replace_sinit(symbol.name, temp_name, Path(source).name)
            symbol.st_name = elf.strtab.add_symbol(symbol.name)
    return elf


def plain_name(name):
    if name.startswith(FUNCTION_PREFIX):
        return name[len(FUNCTION_PREFIX):]
    if name.startswith(SYMBOL_AT):
        return "@" + name[len(SYMBOL_AT):]
    return name.replace(SYMBOL_DOLLAR, "$")


def section_names(elf):
    for section in elf.sections:
        section.name = elf.shstrtab.get_symbol_by_index(section.sh_name)


def functions(elf):
    found = {}
    for index, symbol in enumerate(elf.symtab.symbols):
        if symbol.type == STT_FUNC and 0 < symbol.st_shndx < len(elf.sections):
            found[plain_name(symbol.name)] = index
    return found


def code_sections(elf, names):
    found = functions(elf)
    return {elf.symtab.symbols[found[name]].st_shndx: name for name in names}


def records_for(elf, section_index):
    return [record for record in elf.relocations if record.sh_info == section_index]


def references(elf, section_index):
    return [(relocation.r_offset, relocation.reloc_type, relocation.symbol_index)
            for record in records_for(elf, section_index) for relocation in record.relocations]


def anonymous(elf, symbol_index):
    symbol = elf.symtab.symbols[symbol_index]
    match = ANONYMOUS.fullmatch(symbol.name)
    if not match or symbol.type == STT_SECTION or not 0 < symbol.st_shndx < len(elf.sections):
        return None
    return match.group(1), int(match.group(2))


def own_data(elf, section_index):
    found = {}
    for offset, kind, symbol_index in references(elf, section_index):
        key = anonymous(elf, symbol_index)
        if key:
            found[symbol_index] = key
    return sorted(found, key=lambda index: found[index])


def target_key(elf, symbol_index, pairs, code):
    symbol = elf.symtab.symbols[symbol_index]
    if symbol_index in pairs:
        return ("data", pairs[symbol_index])
    if symbol.type == STT_SECTION:
        return ("section", code.get(symbol.st_shndx, f"section {symbol.st_shndx}"))
    return ("name", plain_name(symbol.name))


def contents(section):
    if section.sh_type == SHT_NOBITS:
        return section.sh_size
    return bytes(section.data)


def view(elf, section_index, pairs, code):
    return (contents(elf.sections[section_index]),
            [(offset, kind, target_key(elf, index, pairs, code))
             for offset, kind, index in references(elf, section_index)])


def pair_data(state, state_text, base, base_text, function):
    state_data = own_data(state, state_text)
    base_data = own_data(base, base_text)
    if [anonymous(state, i)[0] for i in state_data] != [anonymous(base, i)[0] for i in base_data]:
        raise ValueError(f"{function}: the state compile gives it other data "
                         f"({[state.symtab.symbols[i].name for i in state_data]} against "
                         f"{[base.symtab.symbols[i].name for i in base_data]})")
    return dict(zip(state_data, base_data))


def base_symbol(base, key, known, base_code):
    kind, value = key
    if kind == "data":
        return value
    if kind == "section":
        sections = [index for index, name in base_code.items() if name == value]
        for index, symbol in enumerate(base.symtab.symbols):
            if symbol.type == STT_SECTION and symbol.st_shndx in sections:
                return index
        raise ValueError(f"{value}: no section symbol in the object")
    if value in known:
        return known[value]
    matches = [index for index, symbol in enumerate(base.symtab.symbols)
               if index and symbol.type != STT_SECTION and plain_name(symbol.name) == value]
    if not matches:
        raise ValueError(f"{value}: not in the object")
    defined = [index for index in matches if base.symtab.symbols[index].st_shndx]
    return (defined or matches)[0]


def splice_section(base, base_index, state, state_index, pairs, state_code, base_code):
    known = {plain_name(base.symtab.symbols[index].name): index
             for offset, kind, index in references(base, base_index)}
    if base.sections[base_index].sh_type == SHT_NOBITS:
        if contents(base.sections[base_index]) != contents(state.sections[state_index]):
            raise ValueError(f"section {base_index}: uninitialised data of another size")
    else:
        base.sections[base_index].data = bytes(state.sections[state_index].data)
    wanted = [Relocation(offset, (base_symbol(base, target_key(state, index, pairs, state_code),
                                              known, base_code) << 8) | kind)
              for offset, kind, index in references(state, state_index)]
    records = records_for(base, base_index)
    if not records and wanted:
        raise ValueError(f"section {base_index} would gain relocations it does not have")
    for number, record in enumerate(records):
        record.relocations = wanted if number == 0 else []


def splice(base, state, drafts, markers):
    section_names(base)
    section_names(state)
    base_functions = functions(base)
    state_functions = functions(state)
    skip = set(drafts) | set(markers)
    common = [name for name in base_functions if name in state_functions]
    state_code = code_sections(state, common)
    base_code = code_sections(base, common)
    changed = []
    for name in common:
        if name in skip:
            continue
        base_function = base.symtab.symbols[base_functions[name]]
        state_function = state.symtab.symbols[state_functions[name]]
        pairs = pair_data(state, state_function.st_shndx, base, base_function.st_shndx, name)
        same = {index: index for index in pairs.values()}
        data = [(state_index, base_index) for state_index, base_index in pairs.items()
                if view(state, state.symtab.symbols[state_index].st_shndx, pairs, state_code)
                != view(base, base.symtab.symbols[base_index].st_shndx, same, base_code)]
        if (view(state, state_function.st_shndx, pairs, state_code)
                == view(base, base_function.st_shndx, same, base_code) and not data):
            continue
        splice_section(base, base_function.st_shndx, state, state_function.st_shndx,
                       pairs, state_code, base_code)
        base_function.st_size = state_function.st_size
        for state_index, base_index in data:
            state_datum = state.symtab.symbols[state_index]
            base_datum = base.symtab.symbols[base_index]
            if state_datum.st_size != base_datum.st_size:
                raise ValueError(f"{name}: {state_datum.name} ({state_datum.st_size}, sec {state.sections[state_datum.st_shndx].name if hasattr(state.sections[state_datum.st_shndx],'name') else state_datum.st_shndx}) and {base_datum.name} ({base_datum.st_size}) differ in size")
            splice_section(base, base_datum.st_shndx, state, state_datum.st_shndx,
                           pairs, state_code, base_code)
        changed.append(name)
    return changed


def build(obj, source, flags):
    options = unit_options(unit_of(source))
    if not options:
        return 0
    text, drafts, markers = state_source(source.read_text(), options)
    state = compile_text(text, source, flags)
    base = Elf(obj.read_bytes())
    changed = splice(base, state, drafts, markers)
    for name in changed:
        print(f"state: {unit_of(source)}: {name} compiled with the unit's state options", file=sys.stderr)
    if changed:
        obj.write_bytes(base.pack())
    return 0


def objdiff_base(obj, source, flags):
    options = unit_options(unit_of(source))
    text, drafts = prepare(source.read_text(), options)
    elf = compile_text(text, source, flags)
    hidden = {index: symbol for index, symbol in enumerate(elf.symtab.symbols)
              if symbol.type == STT_FUNC and 0 < symbol.st_shndx and plain_name(symbol.name) in drafts}
    outside = {}
    for index, symbol in hidden.items():
        reference = Symbol(elf.strtab.add_symbol(symbol.name), 0, 0, STB_GLOBAL << 4, 0, 0)
        reference.name = symbol.name
        outside[index] = len(elf.symtab.symbols)
        elf.symtab.symbols.append(reference)
        symbol.name = symbol.name + "$state_draft"
        symbol.st_name = elf.strtab.add_symbol(symbol.name)
    for record in elf.relocations:
        for relocation in record.relocations:
            index = relocation.symbol_index
            if index in hidden and record.sh_info != hidden[index].st_shndx:
                relocation.symbol_index = outside[index]
    obj.parent.mkdir(parents=True, exist_ok=True)
    obj.write_bytes(elf.pack())
    return 0


def main():
    if sys.argv[1] == "--objdiff-base":
        return objdiff_base(Path(sys.argv[2]), Path(sys.argv[3]), sys.argv[4:])
    return build(Path(sys.argv[1]), Path(sys.argv[2]), sys.argv[3:])


if __name__ == "__main__":
    sys.exit(main())
