from __future__ import annotations

import tomllib
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any


@dataclass
class ToolConfig:
    name: str
    enabled: bool = True
    path: str | None = None
    install_dir: str | None = None
    extra: dict[str, Any] = field(default_factory=dict)


@dataclass
class RunConfig:
    timeout_s: float = 600.0
    repeats: int = 1
    results_dir: Path = Path("results")


@dataclass
class CorpusConfig:
    dir: Path = Path("corpus/binaries")
    manifest: Path = Path("corpus/manifest.json")
    sources: Path = Path("corpus/sources")


@dataclass
class Config:
    root: Path
    run: RunConfig = field(default_factory=RunConfig)
    corpus: CorpusConfig = field(default_factory=CorpusConfig)
    tools: dict[str, ToolConfig] = field(default_factory=dict)

    @classmethod
    def load(cls, root: Path | None = None) -> "Config":
        root = (root or Path.cwd()).resolve()
        cfg_path = root / "rebench.toml"
        data: dict[str, Any] = {}
        if cfg_path.exists():
            data = tomllib.loads(cfg_path.read_text(encoding="utf-8"))

        run_data = data.get("run", {}) or {}
        run = RunConfig(
            timeout_s=float(run_data.get("timeout_s", RunConfig.timeout_s)),
            repeats=int(run_data.get("repeats", RunConfig.repeats)),
            results_dir=_resolve(root, run_data.get("results_dir", RunConfig.results_dir)),
        )

        corpus_data = data.get("corpus", {}) or {}
        corpus = CorpusConfig(
            dir=_resolve(root, corpus_data.get("dir", CorpusConfig.dir)),
            manifest=_resolve(root, corpus_data.get("manifest", CorpusConfig.manifest)),
            sources=_resolve(root, corpus_data.get("sources", CorpusConfig.sources)),
        )

        tools: dict[str, ToolConfig] = {}
        tools_data = data.get("tools", {}) or {}
        for name, td in tools_data.items():
            td = td or {}
            tools[name] = ToolConfig(
                name=name,
                enabled=bool(td.get("enabled", True)),
                path=td.get("path"),
                install_dir=td.get("install_dir"),
                extra={k: v for k, v in td.items() if k not in {"enabled", "path", "install_dir"}},
            )

        return cls(root=root, run=run, corpus=corpus, tools=tools)


def _resolve(root: Path, value: Any) -> Any:
    if isinstance(value, (str, Path)):
        p = Path(value)
        return p if p.is_absolute() else (root / p)
    return value
