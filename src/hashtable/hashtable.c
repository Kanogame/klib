#include <stdlib.h>
#include <klib/hashtable.h>
#include <klib/matrix.h>

static ht_item HT_DELETED_ITEM = {NULL, NULL};
static int HT_PRIME_1 = 151;
static int HT_PRIME_2 = 163;
static int HT_INITIAL_BASE_SIZE = 53;

// just internal allocator for table
static ht_table *ht_newSized(int base_size, long (*hash)(void*, int), int (*key_compare)(void*, void*)) {
  ht_table* ht = malloc(sizeof(ht_table));
  ht->base_size = base_size;
  ht->hash = hash;
  ht->key_compare = key_compare;

  ht->size = next_prime(ht->base_size);

  ht->count = 0;
  ht->items = calloc(ht->size, sizeof(ht_item*));

  return ht;
  
}

// allocator for el (bucket)
static ht_item *ht_newItem(void *k, void *v) {
  ht_item* i = malloc(sizeof(ht_item));

  i->key = k;
  i->value = v;

  return i;
}

// creating new table by calling allocator
ht_table *ht_new(long (*hash)(void*, int), int (*key_compare)(void*, void*)) {
  return ht_newSized(HT_INITIAL_BASE_SIZE, hash, key_compare);
}

// freeing only struct, because heap does not own actual values (because void*)
static void ht_freeItem(ht_item *i) {
  free(i);
}

// freeing hashtable
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

// resize may happen of insert/delete, based on load factor
// will recreate new table with new size (to avoid breaking collision chains)
// after recreation, new buckets and size will be moved to og table, new will be freed 
static void ht_resize(ht_table* ht, int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }

    // creation of new table
    ht_table* new_ht = ht_newSized(base_size, ht->hash, ht->key_compare);
    for (int i = 0; i < ht->size; i++) {
        ht_item* item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
	    //reinserting values
	    ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // applying changes to og table
    ht->size = new_ht->size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    // moving items back for them to be freed
    new_ht->items = tmp_items;

    // freeing new one
    ht_freeHashTable(new_ht);
}

// doubling size & resize 
static void ht_resize_up(ht_table* ht) {
    int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


// "halfing" size & resize 
static void ht_resize_down(ht_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}

// hashing, this func will try to return number between 0 and size of table (index)
// might have collisions
static int ht_getHash(ht_table* table, void *s, int num_buckets, int attempt) {
  int hash_a = table->hash(s, HT_PRIME_1 * num_buckets);
  int hash_b = table->hash(s, HT_PRIME_2 * num_buckets);
  return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

// will get hash of key, try to insert it
// if collision happens, rehash until no collision
void ht_insert(ht_table *ht, void *key, void *value) {
  const int load = ht->count * 100 / ht->size;
  if (load > 70) {
    ht_resize_up(ht);
  }

  ht_item *item = ht_newItem(key, value);
  int index = ht_getHash(ht, item->key, ht->size, 0);
  ht_item* cur_item = ht->items[index];
  int i = 1;

  while (cur_item != NULL) {
    // collision
    if (cur_item != &HT_DELETED_ITEM) {
      // replace in case we have same key already
      if (ht->key_compare(cur_item->key, key)) {
	ht_freeItem(cur_item);
	ht->items[index] = item;
	return;
      }
    }

    // rehash
    index = ht_getHash(ht, item->key, ht->size, i);
    cur_item = ht->items[index];
    i++;
  }

  // actual insert
  ht->items[index] = item;
  ht->count++;
}

// will get hash of key, and try to search through all collisions
// to find one with mathing key
void *ht_get(ht_table *ht, void *key) {
  int index = ht_getHash(ht, key, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;

  while (item != NULL && item != &HT_DELETED_ITEM) {
    // one of collisions
    if (ht->key_compare(key, item->key)) {
      // key mathed
      return item->value;
    }

    // rehash
    index = ht_getHash(ht, key, ht->size, i);
    item = ht->items[index];
    i++;
  }

  // no such key
  return NULL;
}

// will find the key (like get) and then free it
// not actually deletes anything, to not break any collision chains
void ht_delete(ht_table *ht, void *key) {
  const int load = ht->count * 100 / ht->size;
  if (load < 10) {
    ht_resize_down(ht);
  }

  int index = ht_getHash(ht, key, ht->size, 0);
  ht_item* item = ht->items[index];
  int i = 1;

  while (item != NULL) {
    // one of collisions
    if (ht->key_compare(key, item->key)) {
      // match
      ht_freeItem(item);
      // mark as deleted
      ht->items[index] = &HT_DELETED_ITEM;
      ht->count--;
      break;
    }

    // rehash
    index = ht_getHash(ht, key, ht->size, i);
    item = ht->items[index];
    i++;
  }
}
