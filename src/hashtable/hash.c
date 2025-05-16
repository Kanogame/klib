#include <string.h>
#include <math.h>

int ht_hashStringPrimes(char *s, int a, int m) {
  long hash = 0;
  int len = strlen(s);

  for (int i = 0; i < len; i++) {
    // ACII as radix
    hash += pow(a, len - (i + 1)) * s[i];
    hash = hash % m;
  }

  return (int)hash;
}
