#include <binary-search-tree.h>

#include <stdio.h>


int main(int argc, char const *argv[])
{
    tree_t *tree = tree_create();
    if (tree == NULL)
    {
        return -1;
    }

    printf("tree_add(50)    : %d\n", tree_add(tree, 50, "50"));
    printf("tree_lookup(50) : %s\n", tree_lookup(tree, 50));
    printf("tree_delete(50) : %d\n", tree_delete(tree, 50));
    printf("tree_lookup(50) : %s\n", tree_lookup(tree, 50));
    printf("tree_delete(50) : %d\n", tree_delete(tree, 50));
    printf("tree_size()     : %d\n", tree_size(tree));
/*
    printf("tree_add(3)    : %d\n", tree_add(tree, 50, "50"));
    printf("tree_add(1)    : %d\n", tree_add(tree, 30, "30"));
    printf("tree_add(2)    : %d\n", tree_add(tree, 20, "20"));
    printf("tree_add(0)    : %d\n", tree_add(tree, 40, "40"));
    printf("tree_add(5)    : %d\n", tree_add(tree, 70, "70"));
    printf("tree_add(4)    : %d\n", tree_add(tree, 60, "60"));
    printf("tree_add(6)    : %d\n", tree_add(tree, 80, "80"));
    printf("tree_size()    : %d\n", tree_size(tree));
    printf("tree_min()     : %s\n", tree_min(tree));
    printf("tree_max()     : %s\n", tree_max(tree));
    printf("tree_lookup(5) : %s\n", tree_lookup(tree, 5));
    printf("tree_lookup(2) : %s\n", tree_lookup(tree, 2));
    printf("tree_lookup(1) : %s\n", tree_lookup(tree, 1));


    printf("tree_print_inorder()\n");
    tree_print_inorder(tree);
    printf("\n");
    printf("tree_print_preorder()\n");
    tree_print_preorder(tree);
    printf("\n");
    printf("tree_print_postorder()\n");
    tree_print_postorder(tree);
    printf("\n");

    printf("tree_delete(5) : %d\n", tree_delete(tree, 5));
    printf("tree_lookup(5) : %s\n", tree_lookup(tree, 5));
    printf("tree_size()    : %d\n", tree_size(tree));


    tree_print_inorder(tree);
    printf("\n");
    tree_print_preorder(tree);
    printf("\n");
    tree_print_postorder(tree);
*/
    tree_destroy(&tree);

    return 0;
}
