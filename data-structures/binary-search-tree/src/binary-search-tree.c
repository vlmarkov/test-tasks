#include <stdio.h>
#include <string.h>

#include <binary-search-tree.h>


static void replace_node_(node_t *parent, node_t *node, node_t *child)
{
    if (parent == NULL)
    {
        return;
    }

    if (node == NULL)
    {
        return;
    }

    if (node->key < parent->key)
    {
        parent->left = child;
    }
    else
    {
        parent->right = child;
    }
}

static void delete_node_(tree_t *tree, node_t *parent, node_t *node)
{
    if (tree == NULL)
    {
        return;
    }

    if (node == NULL)
    {
        return;
    }

    // Case 1: node->left is null and node->right is null
    // Case 2: node->left is null or node->right is null
    // Case 3: node->left is not null and node->right is not null 

    if (node->left == NULL) // Case 1 or 2
    {
        replace_node_(parent, node, node->right);
        if (parent == NULL)
        {
            tree->root = node->right; // Remove tree root
        }
    }
    else if (node->right == NULL) // Case 2
    {
        replace_node_(parent, node, node->left);
        if (parent == NULL)
        {
            tree->root = node->left; // Remove tree root
        }
    }
    else // Case 3
    {
        node_t *min = node->right;
        node_t *min_parent = min;
        while (min->left != NULL)
        {
            min_parent = min;
            min = min->left;
        }

        replace_node_(parent, node, min);
        if (parent == NULL)
        {
            tree->root = min; // Remove tree root
        }

        if (node->right != min) // Case 3.1
        {
            min_parent->left = min->right;
            min->left = node->left;
            min->right = node->right;
        }
        else // Case 3.2
        {
            min->left = node->left;
        }
    }
    
    tree->size--;
    free(node);
    return;
}

static void delete_postorder_(node_t *node) 
{
    if (node == NULL)
    {
        return;
    }
  
    delete_postorder_(node->left);
    delete_postorder_(node->right);
    free(node);
}

static void print_postorder_(node_t *node) 
{
    if (node == NULL)
    {
        return;
    }
  
    print_postorder_(node->left);
    print_postorder_(node->right);
    printf("%s\n", node->value);
}

static void print_inorder_(node_t *node) 
{
    if (node == NULL)
    {
        return;
    }
  
    print_inorder_(node->left);
    printf("%s\n", node->value);
    print_inorder_(node->right);
}

static void print_preorder_(node_t *node) 
{
    if (node == NULL)
    {
        return;
    }

    printf("%s\n", node->value);
    print_preorder_(node->left);
    print_preorder_(node->right);
}

tree_t *tree_create()
{
    tree_t *new = calloc(sizeof(tree_t), 1);
    if (new == NULL)
    {
        return NULL;
    }

    new->size = 0;
    new->root = NULL;

    return new;
}

void tree_destroy(tree_t **tree)
{
    if (*tree)
    {
        delete_postorder_((*tree)->root);
        free(*tree);
        *tree = NULL;
    }
}

int tree_add(tree_t *tree, const int key, const char *value)
{
    if (tree == NULL)
    {
        return -1;
    }

    if (value == NULL)
    {
        return -1;
    }

    node_t *parent = tree->root;
    node_t *node = tree->root;
    while (node != NULL)
    {
        parent = node;
        if (node->key < key)
        {
            node = node->right;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
        else
        {
            return -1;
        }
    }

    node_t *new = calloc(sizeof(node_t), 1);
    if (new == NULL)
    {
        return -1;
    }

    new->key = key;
    new->left = NULL;
    new->right = NULL;
    strncpy(new->value, value, sizeof(new->value) - 1);

    if (parent)
    {
        if (parent->key < key)
        {
            parent->right = new;
        }
        else
        {
            parent->left = new;
        }
    }
    else
    {
        tree->root = new;     
    }

    tree->size++;
    return 0;
}

int tree_delete(tree_t *tree, const int key)
{
    if (tree == NULL)
    {
        return -1;
    }

    node_t *parent = NULL;
    node_t *node = tree->root;
    while (node != NULL && node->key != key)
    {
        parent = node;
        if (node->key < key)
        {   
            node = node->right;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
    }
    if (node == NULL)
    {
        return -1;
    }
    
    delete_node_(tree, parent, node);
    return 0;
}

const char *tree_lookup(tree_t *tree, const int key)
{
    if (tree == NULL)
    {
        return NULL;
    }

    node_t *node = tree->root;
    while (node != NULL)
    {
        if (node->key < key)
        {
            node = node->right;
        }
        else if (node->key > key)
        {
            node = node->left;
        }
        else
        {
            return node->value;
        }
    }

    return NULL;
}

const char *tree_min(tree_t *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree->root == NULL)
    {
        return NULL;
    }

    node_t *node = tree->root;
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node->value;
}

const char *tree_max(tree_t *tree)
{
    if (tree == NULL)
    {
        return NULL;
    }
    if (tree->root == NULL)
    {
        return NULL;
    }

    node_t *node = tree->root;
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node->value;
}

int tree_size(tree_t *tree)
{
    if (tree == NULL)
    {
        return -1;
    }
    return tree->size;
}

void tree_print_postorder(tree_t *tree) 
{
    if (tree == NULL)
    {
        return;
    }
  
    print_postorder_(tree->root);
}

void tree_print_inorder(tree_t *tree) 
{
    if (tree == NULL)
    {
        return;
    }
  
    print_inorder_(tree->root);
}

void tree_print_preorder(tree_t *tree) 
{
    if (tree == NULL)
    {
        return;
    }
  
    print_preorder_(tree->root);
}
