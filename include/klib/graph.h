#ifndef KLIB_GRAPH
#define KLIB_GRAPH

typedef struct Graph {
  int value;
  int size;
  struct Graph** links;
} Graph;


Graph* graph_alloc();

Graph* graph_addChild(Graph* parent, int value);

void graph_depth(Graph* startNode);

inline long hash_combine(long current_hash, int value);
#endif
