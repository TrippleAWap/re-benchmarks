#include <stddef.h>
#include <string.h>

volatile size_t rebench_sink3;

const char *skip_ws(const char *s) {
    while (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n') s++;
    return s;
}

int is_digits(const char *s) {
    if (*s == '\0') return 0;
    while (*s) {
        if (*s < '0' || *s > '9') return 0;
        s++;
    }
    return 1;
}

long parse_int(const char *s, const char **end) {
    s = skip_ws(s);
    int neg = 0;
    if (*s == '-') { neg = 1; s++; }
    else if (*s == '+') s++;
    long value = 0;
    while (*s >= '0' && *s <= '9') {
        value = value * 10 + (*s - '0');
        s++;
    }
    if (end) *end = s;
    return neg ? -value : value;
}

long parse_hex(const char *s, const char **end) {
    s = skip_ws(s);
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) s += 2;
    long value = 0;
    for (;;) {
        char c = *s;
        int v;
        if (c >= '0' && c <= '9') v = c - '0';
        else if (c >= 'a' && c <= 'f') v = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') v = c - 'A' + 10;
        else break;
        value = value * 16 + v;
        s++;
    }
    if (end) *end = s;
    return value;
}

size_t tokenize(char *s, char sep, char **tokens, size_t max_tokens) {
    size_t count = 0;
    while (*s && count < max_tokens) {
        s = (char *)skip_ws(s);
        if (*s == '\0') break;
        tokens[count++] = s;
        while (*s && *s != sep) s++;
        if (*s) *s++ = '\0';
    }
    return count;
}

int parse_ipv4(const char *s, unsigned char out[4]) {
    for (int i = 0; i < 4; i++) {
        s = skip_ws(s);
        if (!is_digits(s)) return 0;
        long v = 0;
        int digits = 0;
        while (*s >= '0' && *s <= '9') {
            v = v * 10 + (*s - '0');
            digits++;
            if (digits > 3) return 0;
            s++;
        }
        if (v > 255) return 0;
        out[i] = (unsigned char)v;
        if (i < 3) {
            if (*s != '.') return 0;
            s++;
        }
    }
    return *skip_ws(s) == '\0';
}

size_t url_decode(char *s) {
    char *out = s;
    while (*s) {
        if (*s == '%' && s[1] && s[2]) {
            int hi = s[1], lo = s[2];
            int hv = (hi >= '0' && hi <= '9') ? hi - '0' : (hi >= 'a' && hi <= 'f') ? hi - 'a' + 10 : (hi >= 'A' && hi <= 'F') ? hi - 'A' + 10 : -1;
            int lv = (lo >= '0' && lo <= '9') ? lo - '0' : (lo >= 'a' && lo <= 'f') ? lo - 'a' + 10 : (lo >= 'A' && lo <= 'F') ? lo - 'A' + 10 : -1;
            if (hv >= 0 && lv >= 0) {
                *out++ = (char)(hv * 16 + lv);
                s += 3;
                continue;
            }
        }
        if (*s == '+') { *out++ = ' '; s++; continue; }
        *out++ = *s++;
    }
    *out = '\0';
    return (size_t)(out - s);
}

int match_brackets(const char *s) {
    int depth = 0;
    for (; *s; s++) {
        if (*s == '(' || *s == '[' || *s == '{') depth++;
        else if (*s == ')' || *s == ']' || *s == '}') {
            depth--;
            if (depth < 0) return 0;
        }
    }
    return depth == 0;
}

size_t trim(char *s) {
    char *start = (char *)skip_ws(s);
    size_t len = strlen(start);
    while (len > 0) {
        char c = start[len - 1];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') len--;
        else break;
    }
    memmove(s, start, len);
    s[len] = '\0';
    return len;
}

int main(void) {
    char buf[256];
    strcpy(buf, "  123 -45 0x1F deadbeef ");
    rebench_sink3 += (size_t)parse_int(buf, NULL);
    rebench_sink3 += (size_t)parse_hex(buf, NULL);

    char line[256];
    strcpy(line, "alpha,beta, gamma ,delta");
    char *tokens[16];
    size_t n = tokenize(line, ',', tokens, 16);
    rebench_sink3 += n;

    unsigned char ip[4];
    rebench_sink3 += (size_t)parse_ipv4("192.168.13.37", ip);
    rebench_sink3 += (size_t)!parse_ipv4("999.1.1.1", ip);

    char url[128];
    strcpy(url, "hello%20world%21+a%26b");
    rebench_sink3 += url_decode(url);

    rebench_sink3 += (size_t)match_brackets("([]{})()");
    rebench_sink3 += (size_t)!match_brackets("([)]");

    char padded[64];
    strcpy(padded, "   trim me please   ");
    rebench_sink3 += trim(padded);
    rebench_sink3 += (size_t)is_digits("1337");
    rebench_sink3 += (size_t)!is_digits("13x37");
    return (int)(rebench_sink3 & 1);
}
