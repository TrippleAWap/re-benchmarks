from __future__ import annotations

_FUNCTIONS_TEMPLATE = """
static volatile unsigned long long scale_sink;

static const char *const scale_strings[] = {{
{strings}
}};

{functions}

int main(void) {{
    unsigned long long x = 0x9E3779B97F4A7C15ull;
    x ^= (unsigned long long)(long long)sfn_{last}(1);
    x ^= (unsigned long long)(long long)sfn_{last}(2);
    scale_sink = x;
    return (int)(scale_sink & 1);
}}
"""


def _string_block(count: int) -> str:
    lines = []
    for i in range(count):
        lines.append(
            f'    "scale payload string {i:02d} '
            + "x" * (8 + (i * 7) % 40)
            + '",'
        )
    return "\n".join(lines)


def _function(index: int, total: int) -> str:
    body = []
    body.append(f"long long sfn_{index}(long long x) {{")
    body.append(f"    long long v = x ^ {index * 2654435761}ull;")
    body.append("    v = (v << 13) | (v >> 51);")
    body.append("    v *= 0xFF51AFD7ED558CCDull;")
    body.append("    switch ((int)(x & 3)) {")
    body.append("    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;")
    body.append("    case 1: v -= (long long)(v & 0xFFFF); break;")
    body.append("    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;")
    body.append("    default: v += (long long)((unsigned long long)v % 1000003ull); break;")
    body.append("    }")
    body.append(f"    for (int i = 0; i < {index % 8}; i++) {{")
    body.append("        v = v * 6364136223846793005ull + 1442695040888963407ull;")
    body.append("    }")
    body.append(f"    v += (long long)__builtin_strlen(scale_strings[{index % 64}]);")
    if index > 0:
        body.append(f"    v += sfn_{index - 1}(v);")
        j = (index * 7919 + 13) % index
        if j != index - 1:
            body.append(f"    v += sfn_{j}(x);")
    body.append("    scale_sink = (unsigned long long)v;")
    body.append("    return v;")
    body.append("}")
    return "\n".join(body)


def scale_binary_name(function_count: int) -> str:
    return f"scale_s{function_count}"


def generate_scale_source(function_count: int) -> str:
    if function_count < 2:
        raise ValueError("function_count must be >= 2")
    functions = "\n\n".join(_function(i, function_count) for i in range(function_count))
    return _FUNCTIONS_TEMPLATE.format(
        strings=_string_block(64),
        functions=functions,
        last=function_count - 1,
    )
