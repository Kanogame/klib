#include <stdlib.h>
#include <string.h>
#include <klib/hashtable.h>
#include <klib/matrix.h>

static ht_item HT_DELETED_ITEM = {NULL, NULL};
static int HT_PRIME_1 = 151;
static int HT_PRIME_2 = 163;
static int HT_INITIAL_BASE_SIZE = 53;

static ht_table *ht_newSized(int base_size) {
  ht_table* ht = malloc(sizeof(ht_table));
  ht->base_size = base_size;

  ht->size = next_prime(ht->base_size);

  ht->count = 0;
  ht->items = calloc(ht->size, sizeof(ht_item*));

  return ht;
  
}

static ht_item *ht_newItem(char *k, char *v) {
  ht_item* i = malloc(sizeof(ht_item));

  i->key = strdup(k);
  i->value = strdup(v);

  return i;
}

ht_table *ht_new() {
  return ht_newSized(HT_INITIAL_BASE_SIZE);
}

static void ht_freeItem(ht_item *i) {
  free(i->key);
  free(i->value);
  free(i);
}

void ht_freeHashTable(ht_table *table) {
  for (int i = 0; i < table->size; i++) {
    ht_item* el = table->items[i];
    if (el != NULL && el != &HT_DELETED_ITEM) {
      ht_freeItem(table->items[i]);
    }
  }

  free(table->items);
  free(table);
}


static void ht_resize(ht_table* ht, int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }
    ht_table* new_ht = ht_newSized(base_size);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and items 
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_freeHashTable(new_ht);
}


static void ht_resize_up(ht_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}

static int ht_getHash(char *s, int num_buckets, int attempt) {
  int hash_a = ht_hashStringPrimes(s, HT_PRIME_1, num_buckets);
  int hash_b = ht_hashStringPrimes(s, HT_PRIME_2, num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_table *ht, char *key, char *value) {
  const int load = ht->count * 100 / ht->size;
  if (load > 70) {
    ht_resize_up(ht);
  }

  ht_item *item = ht_newItem(key, value);
  int index = ht_getHash(item->key, ht->size, 0);
  ht_item* cur_item = ht->items[index];
  int i = 1;

  while (cur_item != NULL) {
    if (cur_item != &HT_DELETED_ITEM) {
      if (strcmp(cur_item->key, key) == 0) {
	ht_freeItem(cur_item);
	ht->items[index] = item;
	return;
      }
    }
    index = ht_getHash(item->key, ht->size, i);
    cur_item = ht->items[index];
    i++;
  }

  ht->items[index] = item;
  ht->count++;
}

char *ht_get(ht_table *ht, char *key) {
  int index = ht_getHash(key, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;

  while (item != NULL && item != &HT_DELETED_ITEM) {
    if (strcmp(item->key, key) == 0) {
      return item->value;
    }
    index = ht_getHash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }

  return NULL;
}

void ht_delete(ht_table *ht, char *key) {
  const int load = ht->count * 100 / ht->size;
  if (load < 10) {
    ht_resize_down(ht);
  }

  int index = ht_getHash(key, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;

  while (item != NULL) {
    if (strcmp(item->key, key) == 0) {
      ht_freeItem(item);
      ht->items[index] = &HT_DELETED_ITEM;
      break;
    }
    index = ht_getHash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }
  ht->count--;
}

