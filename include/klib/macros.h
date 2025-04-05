#define XOR_SWAP(a, b)                                                         \
  {                                                                            \
    a ^= b;                                                                    \
    b ^= a;                                                                    \
    a ^= b;                                                                    \
  }
