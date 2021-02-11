#include <stdio.h>

#include <linked-list.h>


double_linked_list_t *double_linked_list_create()
{
    double_linked_list_t *new = calloc(sizeof(double_linked_list_t), 1);
    if (new == NULL)
    {
        return NULL;
    }

    new->size = 0;
    new->head = NULL;

    return new;
}

void double_linked_list_destroy(double_linked_list_t **double_linked_list)
{
    if (*double_linked_list)
    {
        double_linked_list_t *ptr = *double_linked_list;
        for (node_t *i = ptr->head; i != NULL;)
        {
            node_t *del = i;
            i = i->next;
            free(del);
        }
        free(ptr);
        *double_linked_list = NULL;
    }
}

void double_linked_list_print(double_linked_list_t *double_linked_list)
{
    if (double_linked_list == NULL)
    {
        return;
    }

    printf("[DOUBLE LINKED LIST PRINT]: size : %lu\n", double_linked_list->size);

    for (node_t *i = double_linked_list->head; i != NULL; i = i->next)
    {
        printf("[DOUBLE LINKED LIST PRINT]: value[%d]<-value[%d]->value[%d]\n",
            i->prev ? i->prev->value : -1,
            i->value,
            i->next ? i->next->value : -1);
    }
}

void double_linked_list_push_top(double_linked_list_t *double_linked_list, const int value)
{
    if (double_linked_list == NULL)
    {
        return;
    }

    node_t *new = calloc(sizeof(node_t), 1);
    if (new == NULL)
    {
        return;
    }

    new->value = value;
    new->prev = NULL;
    new->next = double_linked_list->head;
    if (new->next)
    {
        new->next->prev = new;
    }

    double_linked_list->head = new;    
    double_linked_list->size++;

    return;
}

int double_linked_list_pop_top(double_linked_list_t *double_linked_list)
{
    if (double_linked_list == NULL)
    {
        return -1;
    }

    if (double_linked_list->head == NULL)
    {
        return -1;
    }

    node_t *ptr = double_linked_list->head;
    const int value = ptr->value;

    double_linked_list->size--;
    double_linked_list->head = double_linked_list->head->next;
    if (double_linked_list->head)
    {
        double_linked_list->head->prev = NULL;
    }

    free(ptr);

    return value;
}

size_t double_linked_list_size(double_linked_list_t *double_linked_list)
{
    if (double_linked_list == NULL)
    {
        return 0;
    }

    return double_linked_list->size;
}

int double_linked_list_lookup(double_linked_list_t *ptr, const int value)
{
    if (ptr == NULL)
    {
        return -1;
    }

    for (node_t *node = ptr->head; node != NULL; node = node->next)
    {
        if (node->value == value)
        {
            return value;
        }
    }
    return -1;
}

void double_linked_list_delete(double_linked_list_t *ptr, const int value)
{
    if (ptr == NULL)
    {
        return;
    }

    for (node_t *node = ptr->head; node != NULL; node = node->next)
    {
        if (node->value == value)
        {
            if (node == ptr->head)
            {
                ptr->head = ptr->head->next;
                if (ptr->head)
                {
                    ptr->head->prev = NULL;
                }
            }
            else
            {
                node_t *prev = node->prev;
                node_t *next = node->next;
                if (prev)
                {
                    prev->next = next;
                }
                if (next)
                {
                    next->prev = prev;
                }
            }
            ptr->size--;
            free(node);
            return;
        }
    }
    return;
}
