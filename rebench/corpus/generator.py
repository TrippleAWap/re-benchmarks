from __future__ import annotations

_FUNCTION_TEMPLATE = """
long long sfn_{index}(long long x) {{
    long long v = x ^ {index}ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {{
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }}
    for (int i = 0; i < {loop}; i++) {{
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }}
    v += (long long)__builtin_strlen(scale_strings[{string_index}]);
{calls}
    scale_sink = (unsigned long long)v;
    return v;
}}
"""

_MAIN_TEMPLATE = """
#include "{header}"

int main(void) {{
    unsigned long long x = 0x9E3779B97F4A7C15ull;
    x ^= (unsigned long long)(long long)sfn_{last}(1);
    x ^= (unsigned long long)(long long)sfn_{last}(2);
    scale_sink = x;
    return (int)(scale_sink & 1);
}}
"""

_HEADER_TEMPLATE = """#ifndef SCALE_{tier}_H
#define SCALE_{tier}_H

static volatile unsigned long long scale_sink;

static const char *const scale_strings[] = {{
{strings}
}};

{prototypes}

#endif
"""

CHUNK_SIZE = 5000


def _string_block(count: int) -> str:
    lines = []
    for i in range(count):
        lines.append(
            f'    "scale payload string {i:02d} '
            + "x" * (8 + (i * 7) % 40)
            + '",'
        )
    return "\n".join(lines)


def scale_binary_name(function_count: int) -> str:
    return f"scale_s{function_count}"


def generate_scale_sources(function_count: int) -> dict[str, str]:
    """Emit {filename: content} for a multi-TU scaling binary.

    Splitting into chunks keeps gcc memory usage bounded; a single TU with
    tens of thousands of functions exhausts cc1.
    """
    if function_count < 2:
        raise ValueError("function_count must be >= 2")

    tier = function_count
    header_name = f"scale_s{tier}.h"
    prototypes = "\n".join(
        f"long long sfn_{i}(long long);" for i in range(function_count)
    )
    header = _HEADER_TEMPLATE.format(
        tier=tier,
        strings=_string_block(64),
        prototypes=prototypes,
    )

    files: dict[str, str] = {header_name: header}

    for start in range(0, function_count, CHUNK_SIZE):
        end = min(start + CHUNK_SIZE, function_count)
        bodies = []
        for i in range(start, end):
            calls = []
            if i > 0:
                calls.append(f"    v += sfn_{i - 1}(v);")
                j = (i * 7919 + 13) % i
                if j != i - 1:
                    calls.append(f"    v += sfn_{j}(x);")
            bodies.append(
                _FUNCTION_TEMPLATE.format(
                    index=i,
                    loop=i % 8,
                    string_index=i % 64,
                    calls="\n".join(calls),
                )
            )
        files[f"scale_s{tier}_part{start // CHUNK_SIZE}.c"] = (
            f'#include "{header_name}"\n\n' + "\n\n".join(bodies)
        )

    files[f"scale_s{tier}_main.c"] = _MAIN_TEMPLATE.format(
        header=header_name, last=function_count - 1
    )
    return files
