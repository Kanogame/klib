#include <klib/list.h>
#include <stdlib.h>

Node *list_Add(Node *top, void *value) {
  Node *newel = (Node *)malloc(sizeof(Node));
  newel->value = value;
  newel->next = top;
  return newel;
}

Node *list_AddQ(Node *top, void *value) {
  Node *newel = (Node *)malloc(sizeof(Node));
  newel->value = value;
  newel->next = NULL;
  Node *last = top;
  if (top == NULL)
    return newel;
  while (last == NULL) {
    last = top->next;
  }
  last->next = newel;
  return top;
}

// list_SearchNext ищет по списку первый равный элемент при помощи equal,
// возвращает предыдущий элемент
Node *list_SearchNext(Node *top, void *value, int equal(void *, void *)) {
  if ((*equal)(top->value, value))
    return top;

  while (top->next) {
    if ((*equal)(top->next->value, value))
      return top;
    top = top->next;
  }
  return NULL;
}

// list_SearchNextAny ищет по списку первый равный элемент при помощи equal,
// возвращает предыдущий элемент, если такого элемента нет, возвращает top
Node *list_SearchNextAny(Node *top, void *value, int equal(void *, void *)) {
  Node *res = list_SearchNext(top, value, equal);
  if (res == NULL)
    return top;
  return res;
}

void *list_Pop(Node **top) {
  Node *temp = *top;
  void* res = (*top)->value;
  *top = temp->next;
  return res;
}

void *list_Remove(Node *top, void *value, int equal(void *, void *)) {
  Node *S = list_SearchNext(top, value, equal);
  Node *D;
  Node *temp = top;
  if (S) {
    if (S == top && (*equal)(S->next, value)) {
      D = top;
      top = top->next;
      free(D);
    } else {
      D = S->next;
      S->next = S->next->next;
      free(D);
    }
    return top;
  }
  return top;
}

Node *list_AddS(Node *top, void *value, int equal(void *, void *),
                int comparator(void *, void *)) {
  Node *s = list_SearchNextAny(top, value, equal);
  Node *s1;
  Node *newel = (Node *)malloc(sizeof(Node));
  newel->value = value;
  if (s == top && (comparator)(s->value, value)) {
    newel->next = top;
    return newel;
  }
  s1 = s->next;
  s->next = newel;
  newel->next = s1;
  return top;
}

static int isNextSame(Node *top) {
  Node *el = top;

  while (el->next) {
    if (el->value == el->next->value) {
      return 1;
    }
    el = el->next;
  }
  return 0;
}
