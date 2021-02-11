#include <linked-list.h>

#include <stdio.h>


int main(int argc, char const *argv[])
{
    double_linked_list_t *double_linked_list = double_linked_list_create();
    if (double_linked_list == NULL)
    {
        return -1;
    }

    double_linked_list_print(double_linked_list);

    double_linked_list_push_top(double_linked_list, 5);
    double_linked_list_print(double_linked_list);
    double_linked_list_push_top(double_linked_list, 10);
    double_linked_list_print(double_linked_list);
    double_linked_list_push_top(double_linked_list, 15);
    double_linked_list_print(double_linked_list);

    printf("double_linked_list_lookup: %d\n", double_linked_list_lookup(double_linked_list, 15));
    printf("double_linked_list_lookup: %d\n", double_linked_list_lookup(double_linked_list, 25));

    double_linked_list_delete(double_linked_list, 15);
    printf("double_linked_list_lookup: %d\n", double_linked_list_lookup(double_linked_list, 15));

    double_linked_list_pop_top(double_linked_list);
    double_linked_list_print(double_linked_list);

    double_linked_list_destroy(&double_linked_list);

    return 0;
}
