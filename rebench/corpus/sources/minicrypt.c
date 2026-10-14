#include <stddef.h>
#include <string.h>

volatile unsigned long long rebench_sink2;

void tea_encrypt(unsigned int v[2], const unsigned int key[4]) {
    unsigned int sum = 0;
    const unsigned int delta = 0x9E3779B9u;
    for (int i = 0; i < 32; i++) {
        sum += delta;
        v[0] += ((v[1] << 4) + key[0]) ^ (v[1] + sum) ^ ((v[1] >> 5) + key[1]);
        v[1] += ((v[0] << 4) + key[2]) ^ (v[0] + sum) ^ ((v[0] >> 5) + key[3]);
    }
}

void tea_decrypt(unsigned int v[2], const unsigned int key[4]) {
    unsigned int sum = 0xC6EF3720u;
    const unsigned int delta = 0x9E3779B9u;
    for (int i = 0; i < 32; i++) {
        v[1] -= ((v[0] << 4) + key[2]) ^ (v[0] + sum) ^ ((v[0] >> 5) + key[3]);
        v[0] -= ((v[1] << 4) + key[0]) ^ (v[1] + sum) ^ ((v[1] >> 5) + key[1]);
        sum -= delta;
    }
}

void xor_stream(unsigned char *buf, size_t len, const unsigned char *key, size_t keylen) {
    for (size_t i = 0; i < len; i++) {
        buf[i] ^= key[i % keylen];
    }
}

static const char B64_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t base64_encode(const unsigned char *in, size_t inlen, char *out, size_t outcap) {
    size_t o = 0;
    for (size_t i = 0; i < inlen; i += 3) {
        unsigned int n = (unsigned int)in[i] << 16;
        if (i + 1 < inlen) n |= (unsigned int)in[i + 1] << 8;
        if (i + 2 < inlen) n |= in[i + 2];
        if (o + 4 > outcap) return 0;
        out[o++] = B64_ALPHABET[(n >> 18) & 63];
        out[o++] = B64_ALPHABET[(n >> 12) & 63];
        out[o++] = (i + 1 < inlen) ? B64_ALPHABET[(n >> 6) & 63] : '=';
        out[o++] = (i + 2 < inlen) ? B64_ALPHABET[n & 63] : '=';
    }
    if (o < outcap) out[o] = '\0';
    return o;
}

static int b64_val(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

size_t base64_decode(const char *in, size_t inlen, unsigned char *out, size_t outcap) {
    size_t o = 0;
    unsigned int acc = 0;
    int bits = 0;
    for (size_t i = 0; i < inlen; i++) {
        int v = b64_val(in[i]);
        if (v < 0) continue;
        acc = (acc << 6) | (unsigned)v;
        bits += 6;
        if (bits >= 8) {
            bits -= 8;
            if (o >= outcap) return 0;
            out[o++] = (unsigned char)((acc >> bits) & 0xFF);
        }
    }
    return o;
}

unsigned lcg_next(unsigned *state) {
    *state = *state * 1103515245u + 12345u;
    return *state;
}

unsigned crc32_simple(const unsigned char *buf, size_t len) {
    unsigned crc = 0xFFFFFFFFu;
    for (size_t i = 0; i < len; i++) {
        crc ^= buf[i];
        for (int b = 0; b < 8; b++) {
            crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1)));
        }
    }
    return crc ^ 0xFFFFFFFFu;
}

void rot13_buf(char *buf) {
    for (; *buf; buf++) {
        if (*buf >= 'a' && *buf <= 'z') *buf = (char)('a' + (*buf - 'a' + 13) % 26);
        else if (*buf >= 'A' && *buf <= 'Z') *buf = (char)('A' + (*buf - 'A' + 13) % 26);
    }
}

unsigned mix_seed(unsigned seed, const char *tag) {
    while (*tag) {
        seed ^= (unsigned char)*tag++;
        seed *= 2654435761u;
    }
    return seed;
}

int main(void) {
    const unsigned int key[4] = {0x01234567u, 0x89ABCDEFu, 0xFEDCBA98u, 0x76543210u};
    unsigned int block[2] = {0xDEADBEEFu, 0xCAFEBABEu};
    tea_encrypt(block, key);
    tea_decrypt(block, key);
    rebench_sink2 += block[0];
    rebench_sink2 += block[1];

    unsigned char data[64];
    unsigned state = 42;
    for (int i = 0; i < 64; i++) data[i] = (unsigned char)(lcg_next(&state) >> 16);
    unsigned char keybuf[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    xor_stream(data, 64, keybuf, 8);
    rebench_sink2 += crc32_simple(data, 64);

    char encoded[96];
    size_t elen = base64_encode(data, 64, encoded, sizeof(encoded));
    unsigned char decoded[64];
    size_t dlen = base64_decode(encoded, elen, decoded, sizeof(decoded));
    rebench_sink2 += dlen;

    char tag[] = "SecretMessage";
    rot13_buf(tag);
    rebench_sink2 += mix_seed(1234, tag);
    return (int)(rebench_sink2 & 1);
}
