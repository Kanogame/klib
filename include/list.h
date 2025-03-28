#ifndef KLIB_LIST
#define KLIB_LIST
// for future reference, see Arrays.List

typedef struct Node {
  void *value;
  struct Node *next;
} Node;

// comparator >=
// equal ==

Node *list_Add(Node *top, void *value);
Node *list_AddQ(Node *top, void *value);
Node *list_SearchNext(Node *top, void *value, int equal(void *, void *));

Node *list_SearchNextAny(Node *top, void *value, int equal(void *, void *));
void *list_Remove(Node *top, void *value, int equal(void *, void *));
Node *list_AddS(Node *top, void *value, int equal(void *, void *),
                int comparator(void *, void *));

Node *listPrintAsInteger(Node *top);
#endif
