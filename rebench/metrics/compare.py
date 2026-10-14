from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

from ..models import SessionResult


@dataclass
class AccuracyScore:
    tool: str
    binary_name: str
    binary_sha256: str
    functions: int
    named_functions: int
    gt_functions: int
    recovery_ratio: float
    name_match_ratio: float | None


def ground_truth_index(manifest: dict) -> dict[str, dict]:
    index: dict[str, dict] = {}
    for entry in manifest.get("entries", []):
        index[entry["sha256"]] = entry
        index[entry["name"]] = entry
    return index


def _norm(name: str) -> str:
    return (name or "").strip().lower()


def score_run(run, entry: dict) -> AccuracyScore:
    gt = entry.get("ground_truth", {})
    gt_count = int(gt.get("function_count", 0))
    gt_names = {_norm(n) for n in gt.get("function_names", [])}
    functions = int(run.stats.get("functions", 0))
    named = int(run.stats.get("named_functions", 0))

    recovery = (functions / gt_count) if gt_count > 0 else 0.0

    name_ratio = None
    recovered_names = run.stats.get("function_names")
    if recovered_names is not None and gt_count > 0:
        matched = sum(1 for n in recovered_names if _norm(n) in gt_names)
        name_ratio = matched / gt_count

    return AccuracyScore(
        tool=run.tool,
        binary_name=entry["name"],
        binary_sha256=entry["sha256"],
        functions=functions,
        named_functions=named,
        gt_functions=gt_count,
        recovery_ratio=recovery,
        name_match_ratio=name_ratio,
    )


def score_session(session: SessionResult, manifest: dict) -> list[AccuracyScore]:
    index = ground_truth_index(manifest)
    grouped: dict[tuple[str, str], list] = {}
    for run in session.runs:
        if not run.ok or run.skipped:
            continue
        entry = index.get(run.binary_sha256) or index.get(run.binary_name)
        if entry is None:
            continue
        grouped.setdefault((run.tool, entry["sha256"]), []).append((run, entry))

    scores: list[AccuracyScore] = []
    for (tool, sha), pairs in grouped.items():
        entry = pairs[0][1]
        n = len(pairs)
        functions = pairs[-1][0].stats.get("functions", 0)
        named = pairs[-1][0].stats.get("named_functions", 0)
        recovery = sum(score_run(run, entry).recovery_ratio for run, _ in pairs) / n
        name_ratios = [
            score_run(run, entry).name_match_ratio
            for run, _ in pairs
            if score_run(run, entry).name_match_ratio is not None
        ]
        name_ratio = sum(name_ratios) / len(name_ratios) if name_ratios else None
        scores.append(
            AccuracyScore(
                tool=tool,
                binary_name=entry["name"],
                binary_sha256=sha,
                functions=functions,
                named_functions=named,
                gt_functions=entry["ground_truth"]["function_count"],
                recovery_ratio=recovery,
                name_match_ratio=name_ratio,
            )
        )
    return scores
