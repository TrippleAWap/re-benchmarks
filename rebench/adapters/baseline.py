from __future__ import annotations

from importlib.metadata import version
from importlib.util import find_spec
from pathlib import Path

from .base import AdapterError, AdapterResult, AnalysisFailedError, ToolAdapter
from .registry import register
from ..models import ToolStatus


@register
class BaselineAdapter(ToolAdapter):
    name = "baseline"
    display_name = "Baseline (pefile)"
    description = "Static PE parsing: imports, exports, sections. No analysis."
    kind = "library"

    def probe(self) -> ToolStatus:
        try:
            v = version("pefile")
        except Exception:
            return ToolStatus(detail="pefile python package not installed")
        return ToolStatus(installed=True, version=v, detail="python pefile")

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        import pefile

        try:
            pe = pefile.PE(str(binary), fast_load=True)
        except pefile.PEFormatError as e:
            raise AnalysisFailedError(f"not a valid PE file: {e}") from e
        except OSError as e:
            raise AnalysisFailedError(f"cannot read binary: {e}") from e

        try:
            pe.parse_data_directories(
                directories=[
                    pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"],
                    pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_EXPORT"],
                ]
            )
            imports = 0
            if hasattr(pe, "DIRECTORY_ENTRY_IMPORT"):
                imports = sum(len(entry.imports) for entry in pe.DIRECTORY_ENTRY_IMPORT)
            exports = 0
            if hasattr(pe, "DIRECTORY_ENTRY_EXPORT") and pe.DIRECTORY_ENTRY_EXPORT.symbols:
                exports = len(pe.DIRECTORY_ENTRY_EXPORT.symbols)
            sections = len(pe.sections)
        finally:
            pe.close()

        return AdapterResult(
            stats={
                "functions": 0,
                "named_functions": 0,
                "imports": imports,
                "exports": exports,
                "sections": sections,
                "strings": 0,
                "symbols": 0,
            },
            notes="static PE metadata only, no analysis",
        )
