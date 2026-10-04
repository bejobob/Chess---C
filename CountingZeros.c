#include <stdint.h>

uint64_t countTrailingZeros(uint64_t x){
    if (x==0) return 64;
    return __builtin_ctzll(x);
}

uint64_t countLeadingZeros(uint64_t x){
    if (x==0) return 64;
    return __builtin_clzll(x);
}