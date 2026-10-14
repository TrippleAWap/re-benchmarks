from __future__ import annotations

import os
from pathlib import Path

from .base import AdapterResult, ToolAdapter
from .registry import register
from ..models import ToolStatus

_SEARCH_ROOTS = (
    Path(r"C:\Program Files"),
    Path(r"C:\Program Files (x86)"),
    Path("C:\\"),
    Path.home(),
)


def _find_headless(install_dir: str | None) -> Path | None:
    candidates: list[Path] = []
    if install_dir:
        candidates.append(Path(install_dir))
    env = os.environ.get("GHIDRA_INSTALL_DIR")
    if env:
        candidates.append(Path(env))
    for root in _SEARCH_ROOTS:
        if not root.exists():
            continue
        for entry in sorted(root.glob("ghidra*"), reverse=True):
            if entry.is_dir():
                candidates.append(entry)
    for c in candidates:
        for script in ("analyzeHeadless.bat", "analyzeHeadless"):
            p = c / "support" / script
            if p.exists():
                return p
        p = c / script
        if c.name.lower().startswith("ghidra") and (c / script).exists():
            return c / script
    return None


@register
class GhidraAdapter(ToolAdapter):
    name = "ghidra"
    display_name = "Ghidra"
    description = "Ghidra headless analysis via analyzeHeadless."
    kind = "cli"

    def probe(self) -> ToolStatus:
        install_dir = self.config.install_dir or os.environ.get("GHIDRA_INSTALL_DIR")
        headless = _find_headless(install_dir)
        if headless is None:
            return ToolStatus(detail="analyzeHeadless not found (set [tools.ghidra] install_dir)")
        v = None
        parent = headless.parent.parent
        if parent.name.lower().startswith("ghidra"):
            v = parent.name.replace("ghidra_", "").replace("ghidra", "").strip("_ ")
        return ToolStatus(installed=True, path=str(headless), version=v, detail=str(parent))

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        raise NotImplementedError
