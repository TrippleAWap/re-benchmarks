from __future__ import annotations

from pathlib import Path

from .base import AdapterResult, ToolAdapter
from .registry import register
from ..models import ToolStatus

_SEARCH_ROOTS = (Path(r"C:\Program Files"), Path(r"C:\Program Files (x86)"))
_HEADLESS_NAMES = ("idat.exe", "idat64.exe")


def _find_idat(install_dir: str | None) -> Path | None:
    candidates: list[Path] = []
    if install_dir:
        candidates.append(Path(install_dir))
    for root in _SEARCH_ROOTS:
        if not root.exists():
            continue
        for entry in sorted(root.glob("IDA*"), reverse=True):
            if entry.is_dir():
                candidates.append(entry)
    for c in candidates:
        for name in _HEADLESS_NAMES:
            p = c / name
            if p.exists():
                return p
    return None


@register
class IdaAdapter(ToolAdapter):
    name = "ida"
    display_name = "IDA"
    description = "IDA headless analysis via idat + IDAPython script."
    kind = "cli"

    def probe(self) -> ToolStatus:
        install_dir = self.config.install_dir
        idat = _find_idat(install_dir)
        if idat is None:
            return ToolStatus(detail="idat/idat64 not found (set [tools.ida] install_dir)")
        v = None
        parent = idat.parent.name
        if "IDA" in parent:
            v = parent.replace("IDA", "").strip(" Professional ")
        return ToolStatus(installed=True, path=str(idat), version=v or None, detail=str(idat.parent))

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        raise NotImplementedError
