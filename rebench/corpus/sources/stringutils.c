#include <stddef.h>
#include <string.h>

volatile size_t rebench_sink;

size_t str_length(const char *s) {
    size_t n = 0;
    while (s[n] != '\0') n++;
    return n;
}

void str_reverse(char *s) {
    size_t n = str_length(s);
    for (size_t i = 0; i < n / 2; i++) {
        char t = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = t;
    }
}

int is_palindrome(const char *s) {
    size_t n = str_length(s);
    for (size_t i = 0; i < n / 2; i++) {
        if (s[i] != s[n - 1 - i]) return 0;
    }
    return 1;
}

int count_vowels(const char *s) {
    int count = 0;
    for (size_t i = 0; s[i]; i++) {
        char c = s[i] | 0x20;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') count++;
    }
    return count;
}

void caesar_shift(char *s, int k) {
    k = ((k % 26) + 26) % 26;
    for (; *s; s++) {
        if (*s >= 'a' && *s <= 'z') *s = (char)('a' + (*s - 'a' + k) % 26);
        else if (*s >= 'A' && *s <= 'Z') *s = (char)('A' + (*s - 'A' + k) % 26);
    }
}

unsigned fnv1a_hash(const char *s) {
    unsigned h = 2166136261u;
    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 16777619u;
    }
    return h;
}

int word_count(const char *s) {
    int count = 0;
    int in_word = 0;
    for (; *s; s++) {
        if (*s == ' ' || *s == '\t' || *s == '\n') in_word = 0;
        else if (!in_word) { in_word = 1; count++; }
    }
    return count;
}

void to_upper(char *s) {
    for (; *s; s++) {
        if (*s >= 'a' && *s <= 'z') *s = (char)(*s - 32);
    }
}

int starts_with(const char *s, const char *prefix) {
    while (*prefix) {
        if (*s++ != *prefix++) return 0;
    }
    return 1;
}

const char *find_char(const char *s, char c) {
    for (; *s; s++) {
        if (*s == c) return s;
    }
    return NULL;
}

int main(void) {
    char buf[128];
    strcpy(buf, "reverse engineering benchmarks");
    rebench_sink = str_length(buf);
    str_reverse(buf);
    to_upper(buf);
    caesar_shift(buf, 7);
    rebench_sink += (size_t)is_palindrome("racecar");
    rebench_sink += (size_t)count_vowels(buf);
    rebench_sink += fnv1a_hash(buf);
    rebench_sink += (size_t)word_count(buf);
    rebench_sink += (size_t)starts_with(buf, "REVER");
    rebench_sink += (size_t)(find_char(buf, 'X') != NULL);
    return (int)(rebench_sink & 1);
}
