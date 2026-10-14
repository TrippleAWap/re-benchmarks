from __future__ import annotations

import subprocess
from pathlib import Path

from .base import (
    AdapterResult,
    AnalysisFailedError,
    ToolAdapter,
    ToolNotInstalledError,
    which_tool,
    unwrap_batch_launcher,
)
from .registry import register
from .util import first_json_list, is_auto_name, json_len, parse_marked_sections, tail
from ..models import ToolStatus

_SEARCH_DIRS = (
    Path(r"C:\Program Files\radare2\bin"),
    Path(r"C:\Program Files (x86)\radare2\bin"),
    Path.home() / "scoop" / "apps" / "radare2" / "current" / "bin",
)

_R2_SCRIPT = (
    "aaa; "
    "?e __R2B_FUNCTIONS__; aflj; "
    "?e __R2B_IMPORTS__; iij; "
    "?e __R2B_SYMBOLS__; isj; "
    "?e __R2B_EXPORTS__; iEj; "
    "?e __R2B_SECTIONS__; iSj; "
    "?e __R2B_STRINGS__; izzj"
)


@register
class R2Adapter(ToolAdapter):
    name = "r2"
    display_name = "radare2"
    description = "Radare2 auto-analysis (aaa) via CLI, JSON output."
    kind = "cli"

    def _resolve_exe(self) -> Path | None:
        candidate = which_tool(
            "REBENCH_R2_PATH",
            self.config.path,
            ("r2", "r2.exe", "rizin", "rizin.exe"),
            _SEARCH_DIRS,
        )
        if candidate is None:
            return None
        exe = unwrap_batch_launcher(candidate)
        if not exe.exists():
            return None
        return exe

    def probe(self) -> ToolStatus:
        exe = self._resolve_exe()
        if exe is None:
            return ToolStatus(detail="r2/rizin not found on PATH")
        v = None
        try:
            out = subprocess.run(
                [str(exe), "-v"], capture_output=True, text=True, timeout=15
            )
            first = (out.stdout or out.stderr).strip().splitlines()
            if first:
                v = first[0].strip()
        except Exception:
            pass
        return ToolStatus(installed=True, path=str(exe), version=v, detail=str(exe))

    def _build_cmd(self, exe: Path, binary: Path) -> list[str] | str:
        args = ["-q", "-e", "scr.color=0", "-c", _R2_SCRIPT, str(binary)]
        if exe.suffix.lower() in (".bat", ".cmd"):
            inner = " ".join([f'"{exe}"'] + [f'"{a}"' if " " in a else a for a in args])
            return f'cmd /d /s /c "{inner}"'
        return [str(exe)] + args

    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult:
        exe = self._resolve_exe()
        if exe is None:
            raise ToolNotInstalledError("r2/rizin not found")
        cmd = self._build_cmd(exe, binary)
        try:
            proc = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=timeout_s,
                encoding="utf-8",
                errors="replace",
            )
        except subprocess.TimeoutExpired:
            raise AnalysisFailedError(f"r2 timed out after {timeout_s:.0f}s") from None
        except OSError as e:
            raise AnalysisFailedError(f"failed to launch r2: {e}") from e

        if proc.returncode != 0:
            raise AnalysisFailedError(
                f"r2 exited with {proc.returncode}: {tail(proc.stderr or proc.stdout)}"
            )

        sections = parse_marked_sections(proc.stdout)
        functions_chunk = sections.get("functions", "")
        n_functions = json_len(functions_chunk)
        if n_functions is None:
            raise AnalysisFailedError(
                f"could not parse r2 function output: {tail(functions_chunk)}"
            )

        names = [str(e.get("name", "")) for e in (first_json_list(functions_chunk) or [])
                 if isinstance(e, dict)]
        named = sum(1 for n in names if not is_auto_name(n))

        stats = {
            "functions": n_functions,
            "named_functions": named,
            "imports": json_len(sections.get("imports", "")) or 0,
            "symbols": json_len(sections.get("symbols", "")) or 0,
            "exports": json_len(sections.get("exports", "")) or 0,
            "sections": json_len(sections.get("sections", "")) or 0,
            "strings": json_len(sections.get("strings", "")) or 0,
            "function_names": names[:10000],
        }
        return AdapterResult(stats=stats, notes="analysis: aaa")
