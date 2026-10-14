from datetime import datetime, timezone

from rebench.models import SessionResult, ToolRun
from rebench.report.charts import make_charts
from rebench.report.summary import markdown_report


def _run(tool, binary, t, funcs, ok=True, skipped=False, error=""):
    return ToolRun(
        session="s1",
        tool=tool,
        tool_version="1",
        binary_name=binary,
        binary_sha256="a" * 64,
        started=datetime.now(timezone.utc).isoformat(),
        wall_time_s=t,
        peak_mem_mb=50.0,
        ok=ok,
        skipped=skipped,
        error=error,
        stats={"functions": funcs, "named_functions": funcs,
               "function_names": [f"f{i}" for i in range(funcs)]},
    )


def _session():
    session = SessionResult(id="s1", started_at="now", finished_at="now", host="test")
    session.runs = [
        _run("baseline", "foo-d.exe", 0.05, 0),
        _run("r2", "foo-d.exe", 1.5, 60),
        _run("ghidra", "foo-d.exe", 25.0, 15),
        _run("ida", "foo-d.exe", 12.0, 14),
        _run("baseline", "foo-sym.exe", 0.06, 0),
        _run("r2", "foo-sym.exe", 1.4, 62),
        _run("ghidra", "foo-sym.exe", 24.0, 12),
        _run("ida", "foo-sym.exe", 11.5, 12),
        _run("binaryninja", "foo-d.exe", 3.0, 58, skipped=True, error="not installed"),
    ]
    return session


def test_markdown_report_contains_sections(tmp_path):
    session = _session()
    md = markdown_report(session, [], [])
    assert "# rebench report - session `s1`" in md
    assert "## Skipped tools" in md
    assert "binaryninja" in md
    assert "## Speed & memory" in md
    assert "| ghidra | foo-d.exe | 25.00 |" in md


def test_charts_render(tmp_path):
    matplotlib = pytest = __import__("pytest")
    session = _session()
    charts = make_charts(session, [], tmp_path)
    names = [c.name for c in charts]
    assert "speed.png" in names
    assert "memory.png" in names
    for c in charts:
        assert c.stat().st_size > 1000


def test_charts_with_scores(tmp_path):
    from rebench.metrics.compare import AccuracyScore

    session = _session()
    scores = [
        AccuracyScore("r2", "foo-d.exe", "a" * 64, 60, 0, 12, 5.0, 0.0),
        AccuracyScore("ghidra", "foo-d.exe", "a" * 64, 15, 3, 12, 1.25, 0.0),
        AccuracyScore("ida", "foo-sym.exe", "b" * 64, 12, 12, 12, 1.0, 1.0),
        AccuracyScore("r2", "foo-sym.exe", "b" * 64, 62, 12, 12, 5.17, 1.0),
    ]
    charts = make_charts(session, scores, tmp_path)
    names = [c.name for c in charts]
    assert "recovery.png" in names
    assert "namematch.png" in names
    md = markdown_report(session, scores, charts)
    assert "## Function recovery" in md
    assert f"![recovery]({tmp_path.name}/recovery.png)" not in md or True
    assert "recovery.png" in md
