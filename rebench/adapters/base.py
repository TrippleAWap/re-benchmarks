from __future__ import annotations

import os
import shutil
from abc import ABC, abstractmethod
from pathlib import Path

from ..config import ToolConfig
from ..models import AdapterResult, ToolStatus

class AdapterError(RuntimeError):
    pass


class ToolNotInstalledError(AdapterError):
    pass


class AnalysisFailedError(AdapterError):
    pass


class ToolAdapter(ABC):
    name: str = ""
    display_name: str = ""
    description: str = ""
    kind: str = "cli"

    def __init__(self, config: ToolConfig, root: Path):
        self.config = config
        self.root = root

    @abstractmethod
    def probe(self) -> ToolStatus: ...

    @abstractmethod
    def analyze(self, binary: Path, timeout_s: float) -> AdapterResult: ...


def find_on_path(names: tuple[str, ...]) -> Path | None:
    for name in names:
        found = shutil.which(name)
        if found:
            return Path(found)
    return None


def find_in_dirs(names: tuple[str, ...], dirs: tuple[Path, ...]) -> Path | None:
    for d in dirs:
        for name in names:
            candidate = d / name
            if candidate.exists():
                return candidate
    return None


def which_tool(env_key: str, config_value: str | None, names: tuple[str, ...],
               search_roots: tuple[Path, ...] = ()) -> Path | None:
    if config_value:
        return Path(config_value)
    env = os.environ.get(env_key)
    if env:
        return Path(env)
    found = find_on_path(names)
    if found:
        return found
    return find_in_dirs(names, search_roots)


def unwrap_batch_launcher(exe: Path) -> Path:
    import re

    if exe.suffix.lower() not in (".bat", ".cmd"):
        return exe
    try:
        content = exe.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return exe

    candidates: list[str] = []
    for m in re.finditer(r'"([^"\r\n]+)"', content):
        candidates.append(m.group(1))
    for m in re.finditer(r'([^\s"&|<>]+\.exe)', content, re.IGNORECASE):
        candidates.append(m.group(1))

    for cand in candidates:
        cand = cand.strip()
        if cand.startswith("@"):
            cand = cand[1:]
        if "%~dp0" in cand:
            cand = cand.replace("%~dp0", str(exe.parent) + "\\")
        p = Path(cand)
        if not p.is_absolute():
            p = exe.parent / cand
        if p.suffix.lower() == ".exe" and p.exists():
            return p
    return exe
