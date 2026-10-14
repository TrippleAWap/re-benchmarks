from __future__ import annotations

import concurrent.futures
from pathlib import Path

from .base import AdapterResult, AnalysisFailedError, ToolAdapter, ToolNotInstalledError
from .registry import register
from ..models import ToolStatus

_AUTO_PREFIXES = ("sub_", "nullptr_sub_", "unexpected_pop_", " thunk", "?")


@register
class BinaryNinjaAdapter(ToolAdapter):
    name = "binaryninja"
    display_name = "Binary Ninja"
    description = "Binary Ninja headless analysis via python API."
    kind = "library"

    def probe(self) -> ToolStatus:
        from importlib.metadata import version
        from importlib.util import find_spec

        if find_spec("binaryninja") is None:
            return ToolStatus(detail="binaryninja python module not installed (needs license)")
        try:
            v = version("binaryninja")
        except Exception:
            v = None
        return ToolStatus(installed=True, version=v, detail="python binaryninja")

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        try:
            import binaryninja
        except ImportError as e:
            raise ToolNotInstalledError(f"binaryninja not importable: {e}") from e

        holder: dict = {}

        def _work() -> dict:
            bv = binaryninja.load(str(binary))
            if bv is None:
                raise AnalysisFailedError("binary ninja failed to open binary")
            holder["bv"] = bv
            try:
                bv.update_analysis_and_wait()
                functions = list(bv.functions)
                names = [f.name or "" for f in functions]
                named = sum(
                    1 for n in names
                    if n and not n.startswith(_AUTO_PREFIXES) and not n[0].isdigit()
                )
                imports = len(
                    bv.get_symbols_of_type(binaryninja.SymbolType.ImportAddressSymbol)
                )
                exports = len(
                    bv.get_symbols_of_type(binaryninja.SymbolType.ExportedFunctionSymbol)
                )
                symbols = len(bv.symbols)
                strings = len(list(bv.strings))
                return {
                    "functions": len(functions),
                    "named_functions": named,
                    "function_names": names[:10000],
                    "imports": imports,
                    "exports": exports,
                    "symbols": symbols,
                    "strings": strings,
                    "sections": len(bv.sections),
                }
            finally:
                bv.file.close()

        executor = concurrent.futures.ThreadPoolExecutor(max_workers=1)
        try:
            future = executor.submit(_work)
            stats = future.result(timeout=timeout_s)
        except concurrent.futures.TimeoutError:
            bv = holder.get("bv")
            if bv is not None:
                try:
                    bv.abort_analysis()
                except Exception:
                    pass
            raise AnalysisFailedError(
                f"binary ninja timed out after {timeout_s:.0f}s"
            ) from None
        except RuntimeError as e:
            raise AnalysisFailedError(f"binary ninja license/launch error: {e}") from e
        finally:
            executor.shutdown(wait=False)

        return AdapterResult(stats=stats, notes="headless analysis")
