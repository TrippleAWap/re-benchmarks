from __future__ import annotations

import os
import shutil
from abc import ABC, abstractmethod
from pathlib import Path

from ..config import ToolConfig
from ..models import AdapterResult, ToolStatus

STAT_KEYS = (
    "functions",
    "named_functions",
    "imports",
    "exports",
    "strings",
    "symbols",
    "sections",
)


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
        p = Path(config_value)
        if p.exists():
            return p
    env = os.environ.get(env_key)
    if env:
        p = Path(env)
        if p.exists():
            return p
    found = find_on_path(names)
    if found:
        return found
    return find_in_dirs(names, search_roots)
