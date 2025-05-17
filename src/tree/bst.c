#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <klib/bst.h>

  bst_Node *bst_newNode(int key) {
      bst_Node *node = (bst_Node *)malloc(sizeof(bst_Node));
      node->data = key;
      node->left = NULL;
      node->right = NULL;
      return node;
  }


  void bst_insert(int key, bst_Node** root) {
    if (*root == NULL) {
      *root = bst_newNode(key);
      return;
    }
    if (key >= (*root)->data) {
      bst_insert(key, &(*root)->right);
    } else {
      bst_insert(key, &(*root)->left);
    }
  }

  void bst_print(bst_Node* root) {
    if (root == NULL) {
        return;
    }
    bst_print(root->left);
    printf("%d\n", root->data);
    bst_print(root->right);
  }

  void print_ascii_tree_helper(bst_Node *root, char *prefix) {
    if (root == NULL) {
        return;
    }

    char newPrefix[256];
    strcpy(newPrefix, prefix);
    strcat(newPrefix, "\t");
    
    print_ascii_tree_helper(root->right, newPrefix);

    printf("%s\t", prefix);
    printf("%d\n", root->data);

    print_ascii_tree_helper(root->left, newPrefix);
}

void print_ascii_tree(bst_Node *root) {
    if (root == NULL) {
        printf("(empty tree)\n");
        return;
    }
    print_ascii_tree_helper(root->right, "");
    printf("%d\n", root->data);
    print_ascii_tree_helper(root->left, "");
}