#pragma once

#include <stdlib.h>


typedef struct node node_t;

struct node
{
    int key;
    char value[10];
    node_t *left;
    node_t *right;
};

typedef struct
{
    node_t *root;
    size_t size;
} tree_t;

tree_t *tree_create();
void tree_destroy(tree_t **tree);
int tree_add(tree_t *tree, const int key, const char *value);
int tree_delete(tree_t *tree, const int key);
const char *tree_lookup(tree_t *tree, const int key);
const char *tree_min(tree_t *tree);
const char *tree_max(tree_t *tree);
int tree_size(tree_t *tree);

void tree_print_postorder(tree_t *tree);
void tree_print_inorder(tree_t *tree);
void tree_print_preorder(tree_t *tree);
 