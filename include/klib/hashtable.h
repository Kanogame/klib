#ifndef KLIB_HASHTABLE_H
#define KLIB_HASHTABLE_H

typedef struct {
  char* key;
  char* value;
} ht_item;

typedef struct {
  int size;
  int base_size;
  int count;
  ht_item** items;
} ht_table;

ht_table *ht_new();
void ht_freeHashTable(ht_table *table);

void ht_insert(ht_table *ht, char *key, char *value);
char *ht_get(ht_table *ht, char *key);
void ht_delete(ht_table *ht, char *key);

int ht_hashStringPrimes(char *s, int a, int m);
#endif
