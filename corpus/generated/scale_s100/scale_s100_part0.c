#include "scale_s100.h"


long long sfn_0(long long x) {
    long long v = x ^ 0ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[0]);

    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_1(long long x) {
    long long v = x ^ 1ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[1]);
    v += sfn_0(v);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_2(long long x) {
    long long v = x ^ 2ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[2]);
    v += sfn_1(v);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_3(long long x) {
    long long v = x ^ 3ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[3]);
    v += sfn_2(v);
    v += sfn_1(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_4(long long x) {
    long long v = x ^ 4ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[4]);
    v += sfn_3(v);
    v += sfn_1(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_5(long long x) {
    long long v = x ^ 5ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[5]);
    v += sfn_4(v);
    v += sfn_3(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_6(long long x) {
    long long v = x ^ 6ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[6]);
    v += sfn_5(v);
    v += sfn_1(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_7(long long x) {
    long long v = x ^ 7ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[7]);
    v += sfn_6(v);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_8(long long x) {
    long long v = x ^ 8ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[8]);
    v += sfn_7(v);
    v += sfn_5(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_9(long long x) {
    long long v = x ^ 9ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[9]);
    v += sfn_8(v);
    v += sfn_4(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_10(long long x) {
    long long v = x ^ 10ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[10]);
    v += sfn_9(v);
    v += sfn_3(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_11(long long x) {
    long long v = x ^ 11ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[11]);
    v += sfn_10(v);
    v += sfn_2(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_12(long long x) {
    long long v = x ^ 12ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[12]);
    v += sfn_11(v);
    v += sfn_1(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_13(long long x) {
    long long v = x ^ 13ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[13]);
    v += sfn_12(v);
    v += sfn_0(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_14(long long x) {
    long long v = x ^ 14ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[14]);
    v += sfn_13(v);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_15(long long x) {
    long long v = x ^ 15ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[15]);
    v += sfn_14(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_16(long long x) {
    long long v = x ^ 16ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[16]);
    v += sfn_15(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_17(long long x) {
    long long v = x ^ 17ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[17]);
    v += sfn_16(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_18(long long x) {
    long long v = x ^ 18ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[18]);
    v += sfn_17(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_19(long long x) {
    long long v = x ^ 19ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[19]);
    v += sfn_18(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_20(long long x) {
    long long v = x ^ 20ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[20]);
    v += sfn_19(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_21(long long x) {
    long long v = x ^ 21ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[21]);
    v += sfn_20(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_22(long long x) {
    long long v = x ^ 22ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[22]);
    v += sfn_21(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_23(long long x) {
    long long v = x ^ 23ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[23]);
    v += sfn_22(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_24(long long x) {
    long long v = x ^ 24ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[24]);
    v += sfn_23(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_25(long long x) {
    long long v = x ^ 25ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[25]);
    v += sfn_24(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_26(long long x) {
    long long v = x ^ 26ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[26]);
    v += sfn_25(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_27(long long x) {
    long long v = x ^ 27ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[27]);
    v += sfn_26(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_28(long long x) {
    long long v = x ^ 28ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[28]);
    v += sfn_27(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_29(long long x) {
    long long v = x ^ 29ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[29]);
    v += sfn_28(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_30(long long x) {
    long long v = x ^ 30ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[30]);
    v += sfn_29(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_31(long long x) {
    long long v = x ^ 31ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[31]);
    v += sfn_30(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_32(long long x) {
    long long v = x ^ 32ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[32]);
    v += sfn_31(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_33(long long x) {
    long long v = x ^ 33ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[33]);
    v += sfn_32(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_34(long long x) {
    long long v = x ^ 34ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[34]);
    v += sfn_33(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_35(long long x) {
    long long v = x ^ 35ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[35]);
    v += sfn_34(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_36(long long x) {
    long long v = x ^ 36ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[36]);
    v += sfn_35(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_37(long long x) {
    long long v = x ^ 37ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[37]);
    v += sfn_36(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_38(long long x) {
    long long v = x ^ 38ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[38]);
    v += sfn_37(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_39(long long x) {
    long long v = x ^ 39ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[39]);
    v += sfn_38(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_40(long long x) {
    long long v = x ^ 40ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[40]);
    v += sfn_39(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_41(long long x) {
    long long v = x ^ 41ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[41]);
    v += sfn_40(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_42(long long x) {
    long long v = x ^ 42ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[42]);
    v += sfn_41(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_43(long long x) {
    long long v = x ^ 43ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[43]);
    v += sfn_42(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_44(long long x) {
    long long v = x ^ 44ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[44]);
    v += sfn_43(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_45(long long x) {
    long long v = x ^ 45ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[45]);
    v += sfn_44(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_46(long long x) {
    long long v = x ^ 46ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[46]);
    v += sfn_45(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_47(long long x) {
    long long v = x ^ 47ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[47]);
    v += sfn_46(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_48(long long x) {
    long long v = x ^ 48ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[48]);
    v += sfn_47(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_49(long long x) {
    long long v = x ^ 49ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[49]);
    v += sfn_48(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_50(long long x) {
    long long v = x ^ 50ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[50]);
    v += sfn_49(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_51(long long x) {
    long long v = x ^ 51ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[51]);
    v += sfn_50(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_52(long long x) {
    long long v = x ^ 52ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[52]);
    v += sfn_51(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_53(long long x) {
    long long v = x ^ 53ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[53]);
    v += sfn_52(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_54(long long x) {
    long long v = x ^ 54ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[54]);
    v += sfn_53(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_55(long long x) {
    long long v = x ^ 55ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[55]);
    v += sfn_54(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_56(long long x) {
    long long v = x ^ 56ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[56]);
    v += sfn_55(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_57(long long x) {
    long long v = x ^ 57ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[57]);
    v += sfn_56(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_58(long long x) {
    long long v = x ^ 58ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[58]);
    v += sfn_57(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_59(long long x) {
    long long v = x ^ 59ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[59]);
    v += sfn_58(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_60(long long x) {
    long long v = x ^ 60ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[60]);
    v += sfn_59(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_61(long long x) {
    long long v = x ^ 61ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[61]);
    v += sfn_60(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_62(long long x) {
    long long v = x ^ 62ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[62]);
    v += sfn_61(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_63(long long x) {
    long long v = x ^ 63ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[63]);
    v += sfn_62(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_64(long long x) {
    long long v = x ^ 64ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[0]);
    v += sfn_63(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_65(long long x) {
    long long v = x ^ 65ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[1]);
    v += sfn_64(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_66(long long x) {
    long long v = x ^ 66ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[2]);
    v += sfn_65(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_67(long long x) {
    long long v = x ^ 67ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[3]);
    v += sfn_66(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_68(long long x) {
    long long v = x ^ 68ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[4]);
    v += sfn_67(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_69(long long x) {
    long long v = x ^ 69ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[5]);
    v += sfn_68(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_70(long long x) {
    long long v = x ^ 70ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[6]);
    v += sfn_69(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_71(long long x) {
    long long v = x ^ 71ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[7]);
    v += sfn_70(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_72(long long x) {
    long long v = x ^ 72ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[8]);
    v += sfn_71(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_73(long long x) {
    long long v = x ^ 73ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[9]);
    v += sfn_72(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_74(long long x) {
    long long v = x ^ 74ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[10]);
    v += sfn_73(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_75(long long x) {
    long long v = x ^ 75ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[11]);
    v += sfn_74(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_76(long long x) {
    long long v = x ^ 76ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[12]);
    v += sfn_75(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_77(long long x) {
    long long v = x ^ 77ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[13]);
    v += sfn_76(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_78(long long x) {
    long long v = x ^ 78ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[14]);
    v += sfn_77(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_79(long long x) {
    long long v = x ^ 79ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[15]);
    v += sfn_78(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_80(long long x) {
    long long v = x ^ 80ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[16]);
    v += sfn_79(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_81(long long x) {
    long long v = x ^ 81ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[17]);
    v += sfn_80(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_82(long long x) {
    long long v = x ^ 82ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[18]);
    v += sfn_81(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_83(long long x) {
    long long v = x ^ 83ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[19]);
    v += sfn_82(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_84(long long x) {
    long long v = x ^ 84ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[20]);
    v += sfn_83(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_85(long long x) {
    long long v = x ^ 85ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[21]);
    v += sfn_84(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_86(long long x) {
    long long v = x ^ 86ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[22]);
    v += sfn_85(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_87(long long x) {
    long long v = x ^ 87ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[23]);
    v += sfn_86(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_88(long long x) {
    long long v = x ^ 88ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[24]);
    v += sfn_87(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_89(long long x) {
    long long v = x ^ 89ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[25]);
    v += sfn_88(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_90(long long x) {
    long long v = x ^ 90ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[26]);
    v += sfn_89(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_91(long long x) {
    long long v = x ^ 91ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[27]);
    v += sfn_90(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_92(long long x) {
    long long v = x ^ 92ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 4; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[28]);
    v += sfn_91(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_93(long long x) {
    long long v = x ^ 93ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 5; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[29]);
    v += sfn_92(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_94(long long x) {
    long long v = x ^ 94ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 6; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[30]);
    v += sfn_93(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_95(long long x) {
    long long v = x ^ 95ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 7; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[31]);
    v += sfn_94(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_96(long long x) {
    long long v = x ^ 96ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 0; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[32]);
    v += sfn_95(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_97(long long x) {
    long long v = x ^ 97ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 1; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[33]);
    v += sfn_96(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_98(long long x) {
    long long v = x ^ 98ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 2; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[34]);
    v += sfn_97(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}



long long sfn_99(long long x) {
    long long v = x ^ 99ull * 2654435761ull;
    v = (v << 13) | (v >> 51);
    v *= 0xFF51AFD7ED558CCDull;
    switch ((int)(x & 3)) {
    case 0: v += (long long)__builtin_popcountll((unsigned long long)v); break;
    case 1: v -= (long long)(v & 0xFFFF); break;
    case 2: v ^= 0xDEADBEEFCAFEBABEull; break;
    default: v += (long long)((unsigned long long)v % 1000003ull); break;
    }
    for (int i = 0; i < 3; i++) {
        v = v * 6364136223846793005ull + 1442695040888963407ull;
    }
    v += (long long)__builtin_strlen(scale_strings[35]);
    v += sfn_98(v);
    v += sfn_13(x);
    scale_sink = (unsigned long long)v;
    return v;
}
