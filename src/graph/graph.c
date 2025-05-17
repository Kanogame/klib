#include <klib/graph.h>
#include <stdlib.h>
#include <stdio.h>
#include <klib/list.h>
#include <klib/hashtable.h>
Graph* graph_alloc() {
    Graph* new = malloc(sizeof(Graph));
    new->size = 0;
    new->links = NULL;
    new->value = 0;
}

int graph_reallocLinks(Graph* parent, int count) {
    if (parent->links == NULL) {
        parent->size = 1;
        parent->links = malloc(sizeof(Graph*) * count);
        return 0;
    }
    parent->size += count;
    parent->links = realloc(parent->links, sizeof(Graph*) * parent->size);
    return parent->size - 1;
}

Graph* graph_addChild(Graph* parent, int value) {
    Graph* child = graph_alloc();
    child->value = value;

    int id = graph_reallocLinks(parent, 1);
    parent->links[id] = child;
}

int graph_eq(void* a, void* b) {
    return a == b;
}

long hash_combine(long current_hash, int value) {
    return current_hash * 31 + value;
}


long hashGraph(void *p, int seed) {
    Graph* g = (Graph*)p;
    if (g == NULL)
        return seed; 

    long hash = seed;

    hash = hash_combine(hash, g->value);
    hash = hash_combine(hash, g->size);
    
    for (int i = 0; i < g->size; i++) {
        int link_ptr = (int)g->links[i];
        hash = hash_combine(hash, link_ptr);
    }
    
    return hash;
}


void graph_depth(Graph* startNode) {
    Node* list = NULL;

    ht_table* table = ht_new(&hashGraph, &graph_eq);
    int exists = 1;


    list = list_Add(list, startNode);

    while (list != NULL) {
        Node** p = &list;
        Graph* node = (Graph*)list_Pop(p);

        int* been = (int*)ht_get(table, node);
        if (been != NULL) {
            continue;
        } 
        ht_insert(table, node, &exists);
        printf("%d\n", node->value);
        for (int i = 0; i < node->size; i++) {
            if (node->links[i]) {
                list = list_Add(list, node->links[i]);
            }
        }
    }
}