#ifndef KLIB_BST
#define KLIB_BST

 typedef struct bst_Node {
    int data;
    struct bst_Node* left;
    struct bst_Node* right;
  } bst_Node;

bst_Node *bst_newNode(int key);

void bst_insert(int key, bst_Node** root);

void bst_print(bst_Node* root);

void print_ascii_tree(bst_Node* root);

#endif
