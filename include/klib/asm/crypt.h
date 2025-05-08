#ifndef KLIB_S_CRYPT_XOR
#define KLIB_S_CRYPT_XOR
#include <stdint.h>

uint32_t rand_xorshift_32(uint32_t state);
uint64_t rand_xorshift_64(uint64_t state);

#endif
