# Satan's Fiddle compiler integration

The PS2 game units use MWCC 3.0-011126 through Satan's Fiddle. The linker uses
plain `wibo`; library and data-only assembly use GNU `as`. The Docker image
builds a pinned Satan's Fiddle revision with the checked-in
`scripts/build/patches/satansfiddle-native-floating-point.patch` and includes
LLDB and an unstripped `wibo`, so local container builds and CI use the same
compiler wrapper. Builds outside the container must apply that patch before
building Satan's Fiddle with its documented Linux, Rust, LLDB and unstripped
`wibo` prerequisites. Reuse the existing checkout in
cloud tasks; no worktree is needed for setup.

The pinned revision is `365415fa2fd7bf69e899044b704b571a64ed4e6c`.
After updating the Dockerfile or compiler patch, rebuild an existing container
image with `REBUILD_IMAGE=1 ./build.sh`.

Objdiff's source-only base objects use the same adapter, profile, options and
logical translation-unit name as the linked objects. They omit mwccgap so
assembly fallbacks remain absent from the native-code metric. The generated
objdiff configuration reads actual base-object symbols and maps sanitized retail
template identities to MWCC's original template spelling.

```sh
export SATANSFIDDLE=/absolute/path/to/satansfiddle
export WIBO_PATH=/absolute/path/to/unstripped/wibo
./build.sh
```

The default profile is `scripts/build/satansfiddle.json`, outside the generated
`ps2/config` tree. `SATANSFIDDLE_CONFIG` can select another JSON profile. Its
compiler version is a consistency check: Satan's Fiddle still verifies the
compiler executable's SHA-256 and the hook signatures. The checked-in profile
starts helper-call history at zero and initializes the floating-point
evaluate-first annotation to false. These deterministic settings establish a
repeatable baseline; matching retail can require documented per-unit overrides.
There is no statefix dependency.

The checked-in translation-unit rows replace artificial discarded helper
functions with measured compiler history: GPR mask `0x30` for the selected units
and `0x10` for `nd_meswin.cpp`, with FPR mask zero. Calibration checks the complete
allocated object and resolved relocation identities, so a pre-existing mismatch
cannot conceal a new change. These rows describe compiler state, not additional
game functions.

The three translation-unit rows for `actionchara.cpp`, `actscript.cpp` and
`nd_meswin.cpp` set `native_floating_point: true`. This compatibility mode
keeps MWCC's floating expression handling intact while retaining the helper
mask initialization and compiler hash/signature checks. It is opt-in; all
other units keep the deterministic floating-point policies above. Expression
or literal override rows for a native-mode unit are rejected as conflicting.

A clean build of `216512e1` reproduces its retail match and 149 passing units.
With current sources, the plain compiler matches `actionchara` and `actscript`;
`nd_meswin` also needs its GPR helper mask `0x10`. Native mode reproduces all
three complete objects without restoring discarded helpers or changing their
game functions. The old `actionchara` expression overrides are removed because
the native path already matches those functions. This mode retains the original
compiler's sensitivity to source changes; edits require the same full object
and linked retail checks as other units.

The cleanup integration passes all 149 object checks and the linked retail
comparison after clean builds with both 12 and 6 jobs. The compiler patch's
15 configuration tests and the adapter's 4 tests also pass.

`scripts/build/mwccgap.sh` supplies `satansfiddle-wibo.py` as mwccgap's
`--wibo-path`. For each of mwccgap's two passes, the adapter preserves every
compiler option and its argument boundary, separates the generated `-o OBJECT`
and source arguments, and creates a private JSON configuration. The compiler
path and options come from that invocation. The adapter passes the original
source basename with `--translation-unit`, so the temporary `.c` in the second
pass selects the same helper masks and floating-point identities. It retains
the actual source path for quoted includes and dependency generation.

Expression overrides identify a translation unit, mangled function, binary32 or
binary64 type and IEEE value bits. An optional `callee` narrows the identity to
arguments of that mangled call target. Each row applies to every occurrence of
its resulting identity. For example, the three `1.0f` arguments in
`_SET_CROSSFADE` need different scheduling: only `CrossFadeOut` is evaluated
first. Its row is:

```json
{
  "translation_unit": "event_func.cpp",
  "function": "_SET_CROSSFADE__FP12RS_STACKDATAi",
  "value_type": "binary32",
  "value_bits": "0x3f800000",
  "callee": "CrossFadeOut__10CFadeInOutFiif",
  "evaluate_first": true
}
```

Unscoped rows apply during annotation and argument consumption. Callee-scoped
rows apply at argument consumption, where a matching scoped row takes precedence
over an unscoped row regardless of configuration order. The consumer hook also
initializes fresh direct constant nodes that bypassed annotation. An explicit
stable selector can adjust verified assignment wrappers and compiler-registered
literal-pool loads; arbitrary variable expressions retain normal annotation.

The adapter selects only the current unit's override rows; Satan's Fiddle rejects
stale selectors within that compilation. Ordinals, instruction addresses and
compiler-arena addresses are not selectors. The 3.0 profile does
not configure literal-reload behavior: the current `-O3,p` constants are immediate,
and no affected alias path has been validated for 3.0's pooled constants under
other options. The pooled-literal alias bug is established for 2.3.3.

CMake tracks the adapter, selected profile and resolved executable as compiler
dependencies. Set the two CMake cache variables explicitly when changing them
after configuration. A missing executable or profile fails with a setup message;
the build does not silently compile through plain `wibo`.

For a focused check after activation, compile one game unit and compare its
object against retail:

```sh
mkdir -p /tmp/chronicletwo-check
scripts/build/mwccgap.sh /tmp/chronicletwo-check/mg_texture.cpp.o \
  /tmp/chronicletwo-check/mg_texture.d ps2/src/mg_texture.cpp \
  -O3,p -strings readonly -c -Cpp_exceptions off -RTTI off \
  -pragma 'divbyzerocheck on' -i ps2/include
sh scripts/build/fixup_sections.sh /tmp/chronicletwo-check/mg_texture.cpp.o
python3 scripts/build/check_objects.py mg_texture --obj-dir /tmp/chronicletwo-check -v
```

Validate calibration with this full wrapper, section fixup and canonical object
checker. Objdiff percentages help locate differences but do not prove exact
bytes and resolved relocations. A corrected function can coexist with known
failures elsewhere in its unit; compare the complete failure list against the
baseline before accepting a row. See [MWCC matching notes](../../docs/MWCC.md).
Use
`python3 -m unittest discover -s scripts/build -p test_satansfiddle.py` for the
adapter's argument, selector, and failure-path checks.
Use `python3 -m unittest discover -s scripts/build -p test_objdiff_config.py`
to check template, local-symbol, and literal-name mappings.
