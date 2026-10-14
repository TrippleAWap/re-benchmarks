from __future__ import annotations

import json
import sys
from pathlib import Path

from .base import AdapterResult, AnalysisFailedError, ToolAdapter, ToolNotInstalledError
from .headless import run_headless_json
from .registry import register
from .util import count_printable_runs, cpu_affinity_list, is_auto_name
from ..models import ToolStatus


def _len_or_zero(obj) -> int:
    try:
        return len(obj)
    except Exception:
        return 0


def _collect_stats(proj, binary_path: str) -> dict:
    functions = [
        f
        for f in proj.kb.functions.values()
        if not f.is_simprocedure and not f.is_alignment
    ]
    names = [f.name or "" for f in functions]
    named = sum(1 for n in names if not is_auto_name(n))
    mo = proj.loader.main_object

    try:
        imports = _len_or_zero(getattr(mo, "imports", None))
    except Exception:
        imports = 0
    try:
        exports = _len_or_zero(getattr(mo, "exports", None))
    except Exception:
        exports = 0

    return {
        "functions": len(functions),
        "named_functions": named,
        "function_names": names[:10000],
        "imports": imports,
        "exports": exports,
        "symbols": len(list(mo.symbols)),
        "sections": len(mo.sections),
        "strings": count_printable_runs(Path(binary_path)),
    }


def _worker_main(binary_path: str, out_path: str) -> int:
    import logging

    for name in ("angr", "pyvex", "cle", "claripy", "pyvex.lifting"):
        logging.getLogger(name).setLevel(logging.CRITICAL)

    try:
        import angr

        proj = angr.Project(binary_path, auto_load_libs=False)
        proj.analyses.CFGFast(normalize=True, show_progressbar=False)
        stats = _collect_stats(proj, binary_path)
        Path(out_path).write_text(json.dumps(stats), encoding="utf-8")
        return 0
    except Exception as e:
        Path(out_path).write_text(
            json.dumps({"error": f"{type(e).__name__}: {e}"}), encoding="utf-8"
        )
        print(f"angr worker failed: {type(e).__name__}: {e}", file=sys.stderr)
        return 1


@register
class AngrAdapter(ToolAdapter):
    name = "angr"
    display_name = "angr"
    description = "angr CFGFast recovery via isolated subprocess."
    kind = "library"

    def probe(self) -> ToolStatus:
        from importlib.metadata import version
        from importlib.util import find_spec

        if find_spec("angr") is None:
            return ToolStatus(detail="angr python package not installed")
        try:
            v = version("angr")
        except Exception:
            v = None
        return ToolStatus(installed=True, version=v, detail="python angr")

    def analyze(self, binary: Path, timeout_s: float, threads: int = 0) -> AdapterResult:
        from importlib.util import find_spec

        if find_spec("angr") is None:
            raise ToolNotInstalledError("angr python package not installed")

        import tempfile

        workdir = Path(tempfile.mkdtemp(prefix="rebench_angr_"))
        out_json = workdir / "stats.json"
        cmd = [
            sys.executable,
            "-m",
            "rebench.adapters.angr",
            str(binary),
            str(out_json),
        ]
        try:
            run_headless_json(
                cmd, out_json, timeout_s, "angr",
                affinity_cpus=cpu_affinity_list(threads),
            )
            stats = json.loads(out_json.read_text(encoding="utf-8"))
        finally:
            import shutil

            shutil.rmtree(workdir, ignore_errors=True)

        if "error" in stats:
            raise AnalysisFailedError(f"angr failed: {stats['error']}")
        return AdapterResult(stats=stats, notes="CFGFast, isolated subprocess")


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("usage: python -m rebench.adapters.angr <binary> <out_json>", file=sys.stderr)
        sys.exit(2)
    sys.exit(_worker_main(sys.argv[1], sys.argv[2]))
