#include <stdio.h>

#include <stack.h>


stack_t *stack_create()
{
    stack_t *new = calloc(sizeof(stack_t), 1);
    if (new == NULL)
    {
        return NULL;
    }

    new->size = 0;
    new->head = NULL;

    return new;
}

void stack_destroy(stack_t **stack)
{
    if (*stack)
    {
        stack_t *ptr = *stack;
        for (node_t *i = ptr->head; i != NULL;)
        {
            node_t *del = i;
            i = i->next;
            free(del);
        }
        free(ptr);
        *stack = NULL;
    }
}

void stack_print(stack_t *stack)
{
    if (stack == NULL)
    {
        return;
    }

    printf("[STACK PRINT]: size : %lu\n", stack->size);

    for (node_t *i = stack->head; i != NULL; i = i->next)
    {
        printf("[STACK PRINT]: value[%d]\n", i->value);
    }
}

void stack_push(stack_t *stack, const int value)
{
    if (stack == NULL)
    {
        return;
    }

    node_t *new = calloc(sizeof(node_t), 1);
    if (new == NULL)
    {
        return;
    }

    new->value = value;
    new->next = stack->head;
    stack->head = new;
    stack->size++;

    return;
}

int stack_pop(stack_t *stack)
{
    if (stack == NULL)
    {
        return -1;
    }

    if (stack->head == NULL)
    {
        return -1;
    }

    node_t *ptr = stack->head;
    const int value = ptr->value;

    stack->size--;
    stack->head = stack->head->next;

    free(ptr);

    return value;
}

size_t stack_size(stack_t *stack)
{
    if (stack == NULL)
    {
        return 0;
    }

    return stack->size;
}
