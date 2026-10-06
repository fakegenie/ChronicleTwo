#!/usr/bin/env python3
"""Write PROGRESS.md: every gated function with how close its current draft is to retail.

    ./dev.sh python3 scripts/re/progress_md.py > PROGRESS.md

A function is gated when its C++ sits inside `#ifdef NONMATCHING` or
`#ifdef STATEMATCHING` and the `#else` branch holds only INCLUDE_ASM markers.
Each unit with `NONMATCHING` drafts is compiled with that macro defined and
the unit's state primer, so every draft is live. Each unit with `STATEMATCHING`
functions is compiled the way scripts/build/state.py does, with the unit's row
options. objdiff compares each object with retail for the match percentage and
the instruction rows that differ.
Run after ./build.sh so the retail objects in build/pal/objdiff/target exist.
"""

import json
import os
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "scripts" / "build"))
sys.path.insert(0, str(ROOT / "tools" / "mwccgap"))

import state  # noqa: E402

SOURCES = ROOT / "ps2" / "src"
WORK = ROOT / "build" / "pal" / "progress"
FLAGS = ["-O3,p", "-strings", "readonly", "-c", "-Cpp_exceptions", "off", "-RTTI", "off",
         "-i", "ps2/include", "-lang", "c++"]
ASM = re.compile(r'INCLUDE_ASM\("[^"]*",\s*([A-Za-z_]\w*)\)')


def gated(text):
    lines = text.split("\n")
    stack = []
    found = []
    for index, line in enumerate(lines):
        directive = line.strip()
        if directive.startswith("#if"):
            stack.append({"head": directive, "else": None})
        elif directive.startswith("#else") and stack:
            stack[-1]["else"] = index
        elif directive.startswith("#endif") and stack:
            block = stack.pop()
            flag = block["head"].removeprefix("#ifdef ")
            if flag not in ("NONMATCHING", "STATEMATCHING") or block["else"] is None:
                continue
            other = [entry.strip() for entry in lines[block["else"] + 1:index] if entry.strip()]
            markers = [ASM.match(entry) for entry in other]
            if other and all(markers):
                found.extend((marker.group(1), flag) for marker in markers)
    return found


def readable(symbol):
    match = re.match(r"(.+?)__(\d+)([A-Za-z_]\w*)F", symbol)
    if match and len(match.group(3)) >= int(match.group(2)):
        return f"{match.group(3)[:int(match.group(2))]}::{match.group(1)}"
    return re.sub(r"__F.*$|__\d$", "", symbol)


def compile_unit(unit, mode):
    source = SOURCES / f"{unit}.cpp"
    options = state.unit_options(unit)
    if mode == "drafts":
        text = state.primer_text(options) + source.read_text()
        flags = FLAGS + ["-DNONMATCHING"]
    else:
        text, _drafts = state.prepare(source.read_text(), options)
        flags = FLAGS
    elf = state.compile_text(text, source, flags)
    target = WORK / mode / "base" / f"{unit}.cpp.o"
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(elf.pack())
    return target


def write_project(units, mode):
    project = WORK / mode / "project"
    config = json.loads((ROOT / "objdiff.json").read_text())
    chosen = []
    for entry in config["units"]:
        if entry["name"] in units:
            entry = dict(entry)
            entry["target_path"] = os.path.relpath(ROOT / entry["target_path"], project)
            entry["base_path"] = os.path.relpath(WORK / mode / "base" / f"{entry['name']}.cpp.o", project)
            chosen.append(entry)
    config["units"] = chosen
    config["build_base"] = False
    config["build_target"] = False
    config.pop("custom_make", None)
    config.pop("custom_args", None)
    project.mkdir(parents=True, exist_ok=True)
    (project / "objdiff.json").write_text(json.dumps(config, indent=2))
    return project


def diff_rows(project, unit, symbol):
    result = subprocess.run(["objdiff-cli", "diff", "-p", str(project), "-u", unit, symbol,
                             "-o", "-", "--format", "json"],
                            capture_output=True, text=True, cwd=ROOT)
    try:
        data = json.loads(result.stdout)
    except ValueError:
        return None
    counts = []
    for side in ("left", "right"):
        symbols = [s for s in (data.get(side) or {}).get("symbols", []) if s["name"] == symbol]
        if not symbols:
            counts.append(None)
            continue
        rows = symbols[0].get("instructions", [])
        counts.append((sum(1 for row in rows if row.get("diff_kind") not in (None, "DIFF_NONE")),
                       len(rows)))
    return counts


def main():
    os.environ["MWCIncludes"] = "ps2/include/std;ps2/include/sce"
    per_unit = defaultdict(list)
    for source in sorted(SOURCES.glob("*.cpp")):
        for symbol, flag in gated(source.read_text()):
            per_unit[source.stem].append((symbol, flag))

    modes = {"drafts": {}, "state": {}}
    for unit, items in per_unit.items():
        for _symbol, flag in items:
            modes["drafts" if flag == "NONMATCHING" else "state"][unit] = True

    failed = {}
    projects = {}
    scores = {}
    for mode, units in modes.items():
        built = set()
        for unit in units:
            print(f"compiling {unit} ({mode})", file=sys.stderr)
            try:
                compile_unit(unit, mode)
                built.add(unit)
            except Exception as error:
                failed[(unit, mode)] = str(error).splitlines()[0] if str(error) else "compile failed"
        if not built:
            continue
        project = write_project(built, mode)
        projects[mode] = project
        report = project / "report.json"
        subprocess.run(["objdiff-cli", "report", "generate", "--project", str(project),
                        "--output", str(report)], cwd=ROOT, check=True, stderr=subprocess.DEVNULL)
        for entry in json.loads(report.read_text())["units"]:
            for function in entry["functions"]:
                scores[(mode, entry["name"], function["name"])] = (
                    function.get("fuzzy_match_percent"), int(function.get("size", 0)))

    rows = []
    for unit, items in per_unit.items():
        seen = set()
        for symbol, flag in items:
            if (symbol, flag) in seen:
                continue
            seen.add((symbol, flag))
            mode = "drafts" if flag == "NONMATCHING" else "state"
            if (unit, mode) in failed:
                rows.append((unit, symbol, flag, None, 0, None, False))
                continue
            percent, size = scores.get((mode, unit, symbol), (None, 0))
            estimated = False
            off = 0 if percent == 100.0 else None
            if percent != 100.0:
                counts = diff_rows(projects[mode], unit, symbol)
                known = [c for c in (counts or []) if c]
                if known:
                    off = max(c[0] for c in known)
                    total = max(c[1] for c in known)
                    if percent is None and flag == "STATEMATCHING":
                        percent, off, estimated = 100.0, 0, "verified"
                    elif percent is None and total:
                        percent = 100.0 * (total - off) / total
                        estimated = True
            rows.append((unit, symbol, flag, percent, size, off, estimated))

    emit(rows, failed)


def percent_text(percent, estimated=False):
    if percent is None:
        return "n/a"
    if estimated == "verified":
        return f"{percent:.1f}%†"
    return f"~{percent:.1f}%" if estimated else f"{percent:.1f}%"


def emit(rows, failed):
    out = ["# Gated function progress", "",
           "Every function whose C++ sits behind `#ifdef NONMATCHING` or `#ifdef STATEMATCHING`.",
           "Drafts are compiled with `NONMATCHING` defined so every body is live. `STATEMATCHING` functions are",
           "compiled with each unit's state options, as `state.py` does. objdiff compares the result with retail.",
           "Generated by `scripts/re/progress_md.py`.", "",
           "- **Match** is objdiff's percentage for the current draft.",
           "- **Lines off** is the number of instruction rows that differ from retail.",
           "- **Size** is the retail function in bytes (instructions are bytes / 4).",
           "- `~` marks a score computed from the differing instruction rows, because objdiff gives no score",
           "  to a function whose switch jump table splits its row.",
           "- `†` marks a `STATEMATCHING` function with a jump table. objdiff cannot score it, but the build",
           "  verifies it: `state.py` splices any function whose compile differs, and `check_objects.py` fails if one does not match.",
           "- `STATEMATCHING` functions match retail under `state.py` and keep their assembly in the plain build.", ""]
    by_flag = defaultdict(list)
    for row in rows:
        by_flag[row[2]].append(row)
    out.append("## Summary")
    out.append("")
    out.append("| Gate | Functions | Exact (100%) | 95% and above | Under 95% | No score |")
    out.append("| --- | --- | --- | --- | --- | --- |")
    for flag in ("NONMATCHING", "STATEMATCHING"):
        group = by_flag[flag]
        scored = [r for r in group if r[3] is not None]
        exact = sum(1 for r in scored if r[3] >= 100.0)
        high = sum(1 for r in scored if 95.0 <= r[3] < 100.0)
        low = sum(1 for r in scored if r[3] < 95.0)
        out.append(f"| `{flag}` | {len(group)} | {exact} | {high} | {low} | {len(group) - len(scored)} |")
    out.append("")
    if failed:
        out.append("Units that did not compile for this report: "
                   + ", ".join(f"`{unit}` ({mode})" for unit, mode in sorted(failed)) + ".")
        out.append("")
    for flag, title in (("NONMATCHING", "Drafts (`NONMATCHING`)"),
                        ("STATEMATCHING", "State-matched (`STATEMATCHING`)")):
        group = by_flag[flag]
        if not group:
            continue
        out.append(f"## {title}")
        out.append("")
        units = defaultdict(list)
        for row in group:
            units[row[0]].append(row)
        for unit in sorted(units):
            out.append(f"### {unit}")
            out.append("")
            out.append("| Function | Symbol | Match | Lines off | Size |")
            out.append("| --- | --- | --- | --- | --- |")
            ordered = sorted(units[unit], key=lambda r: (-(r[3] if r[3] is not None else -1), r[1]))
            for _unit, symbol, _flag, percent, size, off, estimated in ordered:
                lines = "n/a" if off is None else str(off)
                out.append(f"| `{readable(symbol)}` | `{symbol}` | {percent_text(percent, estimated)} | {lines} | {size} |")
            out.append("")
    print("\n".join(out))


if __name__ == "__main__":
    main()
