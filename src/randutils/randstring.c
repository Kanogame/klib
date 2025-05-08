#include <stdlib.h>

char *randutils_genString(int result_size) {
  char *m = malloc(sizeof(char) * result_size);
  char z1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < result_size; i++) {
    m[i] = z1[rand() % 52];
  }
  m[result_size - 1] = '\0';
  return m;
}

char *randutils_genStringAlphabet(char *alphabet, int alphabet_size,
                                  int result_size) {
  char *m = malloc(sizeof(char) * result_size);
  for (int i = 0; i < result_size; i++) {
    m[i] = alphabet[rand() % alphabet_size];
  }
  m[result_size - 1] = '\0';
  return m;
}
