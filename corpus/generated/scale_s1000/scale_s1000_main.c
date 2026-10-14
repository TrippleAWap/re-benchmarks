
#include "scale_s1000.h"

int main(void) {
    unsigned long long x = 0x9E3779B97F4A7C15ull;
    x ^= (unsigned long long)(long long)sfn_999(1);
    x ^= (unsigned long long)(long long)sfn_999(2);
    scale_sink = x;
    return (int)(scale_sink & 1);
}
