#ifndef KLIB_RANDUTILS
#define KLIB_RANDUTILS

char *randutils_genString(int result_size);
char *randutils_genStringAlphabet(char *alphabet, int alphabet_size,
                                  int result_size);

#endif
