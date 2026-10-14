from __future__ import annotations

from importlib.metadata import version
from importlib.util import find_spec
from pathlib import Path

from .base import AdapterResult, ToolAdapter
from .registry import register
from ..models import ToolStatus


@register
class BinaryNinjaAdapter(ToolAdapter):
    name = "binaryninja"
    display_name = "Binary Ninja"
    description = "Binary Ninja headless analysis via python API."
    kind = "library"

    def probe(self) -> ToolStatus:
        if find_spec("binaryninja") is None:
            return ToolStatus(detail="binaryninja python module not installed (needs license)")
        try:
            v = version("binaryninja")
        except Exception:
            v = None
        return ToolStatus(installed=True, version=v, detail="python binaryninja")

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        raise NotImplementedError
