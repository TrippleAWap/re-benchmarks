
static volatile unsigned long long scale_sink;

static const char *const scale_strings[] = {
    "scale payload string 00 xxxxxxxx",
    "scale payload string 01 xxxxxxxxxxxxxxx",
    "scale payload string 02 xxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 03 xxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 04 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 05 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 06 xxxxxxxxxx",
    "scale payload string 07 xxxxxxxxxxxxxxxxx",
    "scale payload string 08 xxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 09 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 10 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 11 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 12 xxxxxxxxxxxx",
    "scale payload string 13 xxxxxxxxxxxxxxxxxxx",
    "scale payload string 14 xxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 15 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 16 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 17 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 18 xxxxxxxxxxxxxx",
    "scale payload string 19 xxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 20 xxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 21 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 22 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 23 xxxxxxxxx",
    "scale payload string 24 xxxxxxxxxxxxxxxx",
    "scale payload string 25 xxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 26 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 27 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 28 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 29 xxxxxxxxxxx",
    "scale payload string 30 xxxxxxxxxxxxxxxxxx",
    "scale payload string 31 xxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 32 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 33 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 34 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 35 xxxxxxxxxxxxx",
    "scale payload string 36 xxxxxxxxxxxxxxxxxxxx",
    "scale payload string 37 xxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 38 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 39 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 40 xxxxxxxx",
    "scale payload string 41 xxxxxxxxxxxxxxx",
    "scale payload string 42 xxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 43 xxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 44 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 45 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 46 xxxxxxxxxx",
    "scale payload string 47 xxxxxxxxxxxxxxxxx",
    "scale payload string 48 xxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 49 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 50 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 51 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 52 xxxxxxxxxxxx",
    "scale payload string 53 xxxxxxxxxxxxxxxxxxx",
    "scale payload string 54 xxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 55 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 56 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 57 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 58 xxxxxxxxxxxxxx",
    "scale payload string 59 xxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 60 xxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 61 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 62 xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx",
    "scale payload string 63 xxxxxxxxx",
};

long long sfn_0(long long x) {
    long long v = x ^ 0ull;
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
    long long v = x ^ 2654435761ull;
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
    long long v = x ^ 5308871522ull;
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
    long long v = x ^ 7963307283ull;
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
    long long v = x ^ 10617743044ull;
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
    long long v = x ^ 13272178805ull;
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
    long long v = x ^ 15926614566ull;
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
    long long v = x ^ 18581050327ull;
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
    long long v = x ^ 21235486088ull;
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
    long long v = x ^ 23889921849ull;
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
    long long v = x ^ 26544357610ull;
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
    long long v = x ^ 29198793371ull;
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
    long long v = x ^ 31853229132ull;
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
    long long v = x ^ 34507664893ull;
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
    long long v = x ^ 37162100654ull;
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
    long long v = x ^ 39816536415ull;
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
    long long v = x ^ 42470972176ull;
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
    long long v = x ^ 45125407937ull;
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
    long long v = x ^ 47779843698ull;
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
    long long v = x ^ 50434279459ull;
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
    long long v = x ^ 53088715220ull;
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
    long long v = x ^ 55743150981ull;
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
    long long v = x ^ 58397586742ull;
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
    long long v = x ^ 61052022503ull;
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
    long long v = x ^ 63706458264ull;
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
    long long v = x ^ 66360894025ull;
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
    long long v = x ^ 69015329786ull;
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
    long long v = x ^ 71669765547ull;
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
    long long v = x ^ 74324201308ull;
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
    long long v = x ^ 76978637069ull;
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
    long long v = x ^ 79633072830ull;
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
    long long v = x ^ 82287508591ull;
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
    long long v = x ^ 84941944352ull;
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
    long long v = x ^ 87596380113ull;
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
    long long v = x ^ 90250815874ull;
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
    long long v = x ^ 92905251635ull;
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
    long long v = x ^ 95559687396ull;
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
    long long v = x ^ 98214123157ull;
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
    long long v = x ^ 100868558918ull;
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
    long long v = x ^ 103522994679ull;
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
    long long v = x ^ 106177430440ull;
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
    long long v = x ^ 108831866201ull;
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
    long long v = x ^ 111486301962ull;
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
    long long v = x ^ 114140737723ull;
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
    long long v = x ^ 116795173484ull;
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
    long long v = x ^ 119449609245ull;
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
    long long v = x ^ 122104045006ull;
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
    long long v = x ^ 124758480767ull;
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
    long long v = x ^ 127412916528ull;
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
    long long v = x ^ 130067352289ull;
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
    long long v = x ^ 132721788050ull;
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
    long long v = x ^ 135376223811ull;
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
    long long v = x ^ 138030659572ull;
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
    long long v = x ^ 140685095333ull;
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
    long long v = x ^ 143339531094ull;
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
    long long v = x ^ 145993966855ull;
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
    long long v = x ^ 148648402616ull;
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
    long long v = x ^ 151302838377ull;
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
    long long v = x ^ 153957274138ull;
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
    long long v = x ^ 156611709899ull;
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
    long long v = x ^ 159266145660ull;
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
    long long v = x ^ 161920581421ull;
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
    long long v = x ^ 164575017182ull;
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
    long long v = x ^ 167229452943ull;
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
    long long v = x ^ 169883888704ull;
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
    long long v = x ^ 172538324465ull;
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
    long long v = x ^ 175192760226ull;
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
    long long v = x ^ 177847195987ull;
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
    long long v = x ^ 180501631748ull;
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
    long long v = x ^ 183156067509ull;
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
    long long v = x ^ 185810503270ull;
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
    long long v = x ^ 188464939031ull;
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
    long long v = x ^ 191119374792ull;
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
    long long v = x ^ 193773810553ull;
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
    long long v = x ^ 196428246314ull;
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
    long long v = x ^ 199082682075ull;
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
    long long v = x ^ 201737117836ull;
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
    long long v = x ^ 204391553597ull;
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
    long long v = x ^ 207045989358ull;
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
    long long v = x ^ 209700425119ull;
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
    long long v = x ^ 212354860880ull;
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
    long long v = x ^ 215009296641ull;
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
    long long v = x ^ 217663732402ull;
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
    long long v = x ^ 220318168163ull;
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
    long long v = x ^ 222972603924ull;
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
    long long v = x ^ 225627039685ull;
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
    long long v = x ^ 228281475446ull;
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
    long long v = x ^ 230935911207ull;
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
    long long v = x ^ 233590346968ull;
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
    long long v = x ^ 236244782729ull;
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
    long long v = x ^ 238899218490ull;
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
    long long v = x ^ 241553654251ull;
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
    long long v = x ^ 244208090012ull;
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
    long long v = x ^ 246862525773ull;
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
    long long v = x ^ 249516961534ull;
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
    long long v = x ^ 252171397295ull;
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
    long long v = x ^ 254825833056ull;
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
    long long v = x ^ 257480268817ull;
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
    long long v = x ^ 260134704578ull;
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
    long long v = x ^ 262789140339ull;
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

int main(void) {
    unsigned long long x = 0x9E3779B97F4A7C15ull;
    x ^= (unsigned long long)(long long)sfn_99(1);
    x ^= (unsigned long long)(long long)sfn_99(2);
    scale_sink = x;
    return (int)(scale_sink & 1);
}
