#ifndef KLIB_HASHTABLE
#define KLIB_HASHTABLE

typedef struct {
  void* key;
  void* value;
} ht_item;

typedef struct {
  int size;
  int base_size;
  int count;
  long (*hash)(void*, int);
  int (*key_compare)(void*, void*);

  ht_item** items;
} ht_table;

ht_table *ht_new(long (*hash)(void*, int), int (*key_compare)(void*, void*));
void ht_freeHashTable(ht_table *table);

void ht_insert(ht_table *ht, void *key, void *value);
void *ht_get(ht_table *ht, void *key);
void ht_delete(ht_table *ht, void *key);

int ht_hashStringPrimes(char *s, int a, int m);
#endif
