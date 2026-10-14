# rebench

Benchmark harness for reverse-engineering tools. Run every installed RE tool
(IDA, Ghidra, Binary Ninja, radare2, angr) against a corpus of binaries, measure
**speed, memory, and function-recovery accuracy**, and produce charts you can
drop straight into a video or post.

## Why it's different

Timing tools alone is weak. rebench compiles the corpus **from its own C
sources**, records the ground-truth function list from the symbol table, then
strips the binaries - so it can score how much each tool actually recovers.

Corpus variants per source:

| variant | flags | stripped | use |
|---|---|---|---|
| `-d`   | `-O0`       | yes | function discovery from nothing |
| `-o2`  | `-O2`       | yes | recovery against optimized code |
| `-sym` | `-O0 -g`    | no  | symbol/name recovery (everyone should win) |

## Install

Windows (Python 3.11+), from the repo root:

```powershell
python -m venv .venv
.venv\Scripts\pip install -e ".[tui,charts,dev]"
```

Toolchain needed to build the corpus: gcc, nm, strip (any mingw64/binutils on PATH).

## Quickstart

```powershell
rebench corpus build     # compile corpus + write ground-truth manifest
rebench list-tools       # what did it detect?
rebench run              # benchmark all enabled tools on the corpus
rebench ui               # same, but in the live TUI dashboard
rebench report           # charts + markdown report for the latest session
```

Useful flags:

```powershell
rebench run --tools ida,r2 --repeats 3 --timeout 900 --tag "my run"
rebench run --binary C:\path\to\target.exe
rebench report --session 20261014-010446-b37120
```

Results land in `results/<session-id>.jsonl`; reports in `results/report-<id>/`
(`report.md` + `speed.png`, `memory.png`, `recovery.png`, `namematch.png`).

## Tools & detection

| tool | kind | detection |
|---|---|---|
| baseline (pefile) | python lib | installed with rebench |
| radare2 / rizin | CLI (`aaa` + JSON) | PATH, common install dirs |
| Ghidra | headless `analyzeHeadless` | `GHIDRA_INSTALL_DIR` env or `[tools.ghidra] install_dir` |
| IDA | `idat.exe` + IDAPython | `C:\Program Files\IDA*` or `[tools.ida] install_dir` |
| Binary Ninja | python API | `binaryninja` module (needs license) |
| angr | python API | `angr` module |

Missing tools are skipped gracefully and recorded as `skipped` in the session -
the report still works with whatever you have installed.

Configure overrides in `rebench.toml`:

```toml
[run]
timeout_s = 600
repeats = 1

[tools.ida]
install_dir = "C:\\Program Files\\IDA Professional 9.2"

[tools.angr]
enabled = false
```

## Metrics

- **wall time** per analysis and **peak memory** (process tree, psutil)
- **functions found** vs ground truth -> `recovery_ratio`
- **name match ratio** on unstripped builds (who reads symbol tables correctly)
- imports / exports / strings / symbols counts per tool

## Adding a tool

Subclass `ToolAdapter` in `rebench/adapters/`, register it, implement
`probe()` (detection) and `analyze(binary, timeout_s)` returning
`AdapterResult(stats={...}, artifacts=[...])`. Standard stat keys live in
`rebench/adapters/base.py`. CLI tools: spawn a subprocess, parse JSON, raise
`AnalysisFailedError` on failure (timeouts kill the whole process tree).
Library tools: run in-process, the runner monitors memory either way.

## Known limitations

- IDA: adapter follows IDA 9.x headless semantics (`idat -A -S script -o db`).
  On installs with a broken/nonstandard `idat` loader chain it will record a
  clean failure instead of a bogus number.
- Binary Ninja / angr: not yet implemented beyond detection (stubs raise
  `NotImplementedError` and show as skipped).
- PE-focused right now; ELF corpus support is a natural next step.

## Development

```powershell
.venv\Scripts\python -m pytest tests -q
```

Tests skip gracefully when a tool or a Windows PE isn't available; the Ghidra
adapter is covered by a mock headless script so it's verified without Ghidra.
