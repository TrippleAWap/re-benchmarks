from __future__ import annotations

from importlib.metadata import version
from importlib.util import find_spec
from pathlib import Path

from .base import AdapterResult, ToolAdapter
from .registry import register
from ..models import ToolStatus


@register
class AngrAdapter(ToolAdapter):
    name = "angr"
    display_name = "angr"
    description = "angr CFG recovery via python API."
    kind = "library"

    def probe(self) -> ToolStatus:
        if find_spec("angr") is None:
            return ToolStatus(detail="angr python package not installed")
        try:
            v = version("angr")
        except Exception:
            v = None
        return ToolStatus(installed=True, version=v, detail="python angr")

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        raise NotImplementedError
