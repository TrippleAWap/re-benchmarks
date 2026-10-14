from __future__ import annotations

import hashlib
from dataclasses import dataclass, field
from datetime import datetime, timezone
from pathlib import Path
from typing import Any


def utcnow() -> datetime:
    return datetime.now(timezone.utc)


def sha256_file(path: Path) -> str:
    h = hashlib.sha256()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


@dataclass
class BinaryInfo:
    path: Path
    sha256: str = ""
    size_bytes: int = 0

    @classmethod
    def from_path(cls, path: Path) -> "BinaryInfo":
        path = Path(path)
        return cls(path=path, sha256=sha256_file(path), size_bytes=path.stat().st_size)


@dataclass
class ToolStatus:
    installed: bool = False
    path: str | None = None
    version: str | None = None
    detail: str = ""


@dataclass
class AdapterResult:
    stats: dict[str, Any] = field(default_factory=dict)
    artifacts: list[Path] = field(default_factory=list)
    notes: str = ""


@dataclass
class ToolRun:
    session: str
    tool: str
    tool_version: str | None
    binary_name: str
    binary_sha256: str
    started: str
    wall_time_s: float
    peak_mem_mb: float
    ok: bool
    skipped: bool
    error: str
    stats: dict[str, Any] = field(default_factory=dict)
    artifacts: list[str] = field(default_factory=list)
    notes: str = ""
    repeat: int = 0


@dataclass
class SessionResult:
    id: str
    started_at: str
    finished_at: str
    host: str
    tag: str = ""
    runs: list[ToolRun] = field(default_factory=list)
