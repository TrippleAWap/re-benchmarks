from __future__ import annotations

import json

import psutil

AUTO_NAME_PREFIXES = (
    "fcn.",
    "loc.",
    "sub.",
    "sym.func.",
    "sym.imp.",
    "imp.",
    "thunk_FUN_",
    "FUN_",
    "@",
    "0x",
)


def is_auto_name(name: str) -> bool:
    if not name:
        return True
    if name.startswith(AUTO_NAME_PREFIXES):
        return True
    return name[0].isdigit()


def json_len(chunk: str) -> int | None:
    chunk = chunk.strip()
    if not chunk:
        return None
    try:
        obj = json.loads(chunk)
        return len(obj) if isinstance(obj, list) else 1
    except json.JSONDecodeError:
        pass
    decoder = json.JSONDecoder()
    idx = 0
    while idx < len(chunk):
        while idx < len(chunk) and chunk[idx] not in "[{":
            idx += 1
        if idx >= len(chunk):
            return None
        try:
            obj, end = decoder.raw_decode(chunk, idx)
            return len(obj) if isinstance(obj, list) else 1
        except json.JSONDecodeError:
            idx += 1
    return None


def first_json_list(chunk: str) -> list | None:
    chunk = chunk.strip()
    if not chunk:
        return None
    decoder = json.JSONDecoder()
    idx = 0
    while idx < len(chunk):
        while idx < len(chunk) and chunk[idx] != "[":
            idx += 1
        if idx >= len(chunk):
            return None
        try:
            obj, _ = decoder.raw_decode(chunk, idx)
            return obj if isinstance(obj, list) else None
        except json.JSONDecodeError:
            idx += 1
    return None


def parse_marked_sections(text: str, prefix: str = "R2B_") -> dict[str, str]:
    sections: dict[str, list[str]] = {}
    current: str | None = None
    for line in text.splitlines():
        stripped = line.strip()
        if stripped.startswith("__") and stripped.endswith("__") and prefix in stripped:
            current = stripped.strip("_").lower().replace(prefix.lower(), "")
            sections[current] = []
        elif current is not None:
            sections[current].append(line)
    return {k: "\n".join(v).strip() for k, v in sections.items()}


def kill_tree(pid: int) -> None:
    try:
        parent = psutil.Process(pid)
    except psutil.Error:
        return
    for child in parent.children(recursive=True):
        try:
            child.kill()
        except psutil.Error:
            pass
    try:
        parent.kill()
    except psutil.Error:
        pass


def tail(text: str, length: int = 400) -> str:
    text = (text or "").strip()
    if len(text) <= length:
        return text
    return "..." + text[-length:]
