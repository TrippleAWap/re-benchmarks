from __future__ import annotations

from importlib.metadata import version
from importlib.util import find_spec
from pathlib import Path

from .base import AdapterResult, ToolAdapter
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
        raise NotImplementedError
