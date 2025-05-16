#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int substring_searchSimple(char *source, char *sub) {
  int i = 0;
  int j = 0;
  int start = -1;
  while (source[i] != '\0') {
    if (sub[j] == '\0') {
      return start; 
    }
    if (source[i] == sub[j]) {
      if (j == 0) {
	start = i;
      }
      j++;
    } else {
      if (start != -1) {
        i = start;
      }
      start = -1;
      j = 0;
    }

    i++;
  }
  // edge case, source="hello" sub="lol"  
  if (sub[j] == '\0') {
    return start;
  }
  return -1;
}

static int *kmpShift(char *sub, int size) {
  int* res = calloc(size, sizeof(int));
  res[0] = -1;

  if (size < 2) {
    return res;
  }
  
  // len from start
  int len = 0;
  int i = 1;
  while (i < size) {
    if (sub[len] == sub[i]) {
      len++;
      i++;
      res[i] = len;
    } else {
      if (len) {
	len = res[len - 1];
      } else {
	i++;
      }
    }
  }
  return res;
}

int substring_searchKmp(char *source, char *sub) {
  int subsize = strlen(sub);
  int srcsize = strlen(source);

  int *shift = kmpShift(sub, subsize);


  int i = 0;
  int j = 0;
  int start = -1;
  while (i < srcsize) {
    if (j >= subsize) {
      return start;
    }
    if (source[i] == sub[j]) {
      if (j == 0) {
	start = i;
      }
      j++;
    } else {
      if (start != -1) {
	i = start + j - shift[j] - 1;
      }
      start = -1;
      j = 0;
    }
    i++;
  }

  // edge case, source="hello" sub="lol"  
  if (sub[j] == '\0') {
    return start;
  }
  return -1;
}

const int charsize = 256;

static int* bch(char *sub, int size) {
  int *map = malloc(charsize * sizeof(int));

  for (int i = 0; i < charsize; i++) {
    map[i] = -1;
  }

  for (int i = 0; i < size; i++) {
    map[(int)(sub[i])] = i;
  }
  return map;
}

int substring_searchBoyerMoore(char *source, char *sub) {
  int subsize = strlen(sub);
  int srcsize = strlen(source);

  int* map = bch(sub, subsize);

  int size = subsize -1;
  int s = 0;
  int j = size;
  while (s <= (srcsize - subsize)) {
    if (j < 0) {
      return s;
    }
    if (source[s+j] == sub[j]) {
      j--;
    } else {
      int pos = j - map[(int)source[s + j]];
      s += pos > 1 ? pos : 1;
      j = size;
    }
  }
  return -1;
}
