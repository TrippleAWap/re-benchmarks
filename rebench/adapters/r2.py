from __future__ import annotations

from pathlib import Path

from .base import AdapterResult, ToolAdapter, which_tool
from .registry import register
from ..models import ToolStatus

_SEARCH_DIRS = (
    Path(r"C:\Program Files\radare2\bin"),
    Path(r"C:\Program Files (x86)\radare2\bin"),
    Path.home() / "scoop" / "apps" / "radare2" / "current" / "bin",
)


@register
class R2Adapter(ToolAdapter):
    name = "r2"
    display_name = "radare2"
    description = "Radare2 auto-analysis (aaa) via CLI, JSON output."
    kind = "cli"

    def probe(self) -> ToolStatus:
        exe = which_tool("REBENCH_R2_PATH", self.config.path, ("r2", "r2.exe", "rizin", "rizin.exe"), _SEARCH_DIRS)
        if exe is None:
            return ToolStatus(detail="r2/rizin not found on PATH")
        v = None
        try:
            import subprocess

            out = subprocess.run([str(exe), "-v"], capture_output=True, text=True, timeout=15)
            first = (out.stdout or out.stderr).strip().splitlines()
            if first:
                v = first[0].strip()
        except Exception:
            pass
        return ToolStatus(installed=True, path=str(exe), version=v, detail=exe.name)

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        raise NotImplementedError
