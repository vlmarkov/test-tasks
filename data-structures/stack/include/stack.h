#pragma once

#include <stdlib.h>

typedef struct node_t node_t;

struct node_t
{
    int value;
    node_t *next;
};

typedef struct
{
    node_t *head;
    size_t size;
} stack_t;

stack_t *stack_create();
void stack_destroy(stack_t **stack);
void stack_print(stack_t *stack);
void stack_push(stack_t *stack, const int value);
int stack_pop(stack_t *stack);
size_t stack_size(stack_t *stack);
