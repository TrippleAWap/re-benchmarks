from __future__ import annotations

import multiprocessing
from pathlib import Path

from .base import AdapterResult, AnalysisFailedError, ToolAdapter, ToolNotInstalledError
from .registry import register
from .util import count_printable_runs, is_auto_name
from ..models import ToolStatus

NO_RESULT_TIMEOUT_S = 15.0


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


def _angr_worker(binary_path: str, queue) -> None:
    try:
        import logging

        for name in ("angr", "pyvex", "cle", "claripy", "pyvex.lifting"):
            logging.getLogger(name).setLevel(logging.CRITICAL)

        import angr

        proj = angr.Project(binary_path, auto_load_libs=False)
        proj.analyses.CFGFast(normalize=True, show_progressbar=False)
        queue.put(("ok", _collect_stats(proj, binary_path)))
    except Exception as e:
        try:
            queue.put(("error", f"{type(e).__name__}: {e}"))
        except Exception:
            pass


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

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        from importlib.util import find_spec

        if find_spec("angr") is None:
            raise ToolNotInstalledError("angr python package not installed")

        ctx = multiprocessing.get_context("spawn")
        queue = ctx.Queue()
        proc = ctx.Process(
            target=_angr_worker, args=(str(binary), queue), daemon=True
        )
        try:
            proc.start()
        except OSError as e:
            raise AnalysisFailedError(f"failed to spawn angr worker: {e}") from e

        proc.join(timeout=timeout_s)
        if proc.is_alive():
            proc.terminate()
            proc.join(5)
            raise AnalysisFailedError(f"angr timed out after {timeout_s:.0f}s")

        if queue.empty():
            raise AnalysisFailedError(
                f"angr produced no result (exit code {proc.exitcode})"
            )
        try:
            status, payload = queue.get(timeout=NO_RESULT_TIMEOUT_S)
        except Exception:
            raise AnalysisFailedError("angr result queue read failed") from None

        if status == "error":
            raise AnalysisFailedError(f"angr failed: {payload}")
        return AdapterResult(stats=payload, notes="CFGFast, isolated subprocess")
