from __future__ import annotations

from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from ..config import Config
    from .base import ToolAdapter

_REGISTRY: dict[str, type["ToolAdapter"]] = {}


def register(cls: type["ToolAdapter"]) -> type["ToolAdapter"]:
    if not cls.name:
        raise ValueError(f"adapter {cls.__name__} has no name")
    _REGISTRY[cls.name] = cls
    return cls


def adapter_classes() -> dict[str, type["ToolAdapter"]]:
    return dict(_REGISTRY)


def build_adapters(config: "Config") -> list["ToolAdapter"]:
    out: list[ToolAdapter] = []
    for name, cls in _REGISTRY.items():
        tc = config.tools.get(name)
        effective = tc if tc is not None else _default_tool_config(name)
        out.append(cls(effective, config.root))
    return out


def _default_tool_config(name: str) -> "ToolConfig":
    from ..config import ToolConfig

    return ToolConfig(name=name)
