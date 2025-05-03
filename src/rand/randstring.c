#include <stdlib.h>

char *generate_string(int len) {
  char *m = malloc(sizeof(char) * len);
  char z1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < len; i++) {
    m[i] = z1[rand() % 52];
  }
  m[len - 1] = '\0';
  return m;
}
