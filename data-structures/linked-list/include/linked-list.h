#pragma once

#include <stdlib.h>


typedef struct node_t node_t;

struct node_t
{
    int value;
    node_t *next;
    node_t *prev;
};

typedef struct
{
    node_t *head;
    size_t size;
} double_linked_list_t;

double_linked_list_t *double_linked_list_create();
void double_linked_list_destroy(double_linked_list_t **double_linked_list);
void double_linked_list_print(double_linked_list_t *double_linked_list);
void double_linked_list_push_top(double_linked_list_t *double_linked_list, const int value);
int double_linked_list_pop_top(double_linked_list_t *double_linked_list);
size_t double_linked_list_size(double_linked_list_t *double_linked_list);
int double_linked_list_lookup(double_linked_list_t *double_linked_list, const int value);
void double_linked_list_delete(double_linked_list_t *double_linked_list, const int value);
