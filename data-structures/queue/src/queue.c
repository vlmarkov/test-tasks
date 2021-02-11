#include <stdio.h>

#include <queue.h>


double_ended_queue_t *double_ended_queue_create()
{
    double_ended_queue_t *new = calloc(sizeof(double_ended_queue_t), 1);
    if (new == NULL)
    {
        return NULL;
    }

    new->size = 0;
    new->head = NULL;
    new->tail = NULL;

    return new;
}

void double_ended_queue_destroy(double_ended_queue_t **queue)
{
    if (*queue)
    {
        double_ended_queue_t *ptr = *queue;
        for (node_t *i = ptr->head; i != NULL;)
        {
            node_t *del = i;
            i = i->next;
            free(del);
        }
        free(ptr);
        *queue = NULL;
    }
}

void double_ended_queue_print(double_ended_queue_t *queue)
{
    if (queue == NULL)
    {
        return;
    }

    printf("[DOUBLE ENDED QUEUE PRINT]: size : %lu\n", queue->size);

    for (node_t *i = queue->head; i != NULL; i = i->next)
    {
        printf("[DOUBLE ENDED QUEUE PRINT]: value[%d]<-value[%d]->value[%d]\n",
            i->prev ? i->prev->value : -1,
            i->value,
            i->next ? i->next->value : -1);
    }
}

void double_ended_queue_push_top(double_ended_queue_t *queue, const int value)
{
    if (queue == NULL)
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
    new->next = queue->head;
    if (new->next)
    {
        new->next->prev = new;
    }

    if (queue->tail == NULL)
    {
        queue->tail = new;
    }

    queue->head = new;
    queue->size++;

    return;
}

void double_ended_queue_push_tail(double_ended_queue_t *queue, const int value)
{
    if (queue == NULL)
    {
        return;
    }

    node_t *new = calloc(sizeof(node_t), 1);
    if (new == NULL)
    {
        return;
    }

    new->value = value;
    new->next = NULL;
    new->prev = queue->tail;
    if (new->prev)
    {
        new->prev->next = new;
    }

    if (queue->head == NULL)
    {
        queue->head = new;
    }

    queue->tail = new;
    queue->size++;

    return;
}

int double_ended_queue_pop_top(double_ended_queue_t *queue)
{
    if (queue == NULL)
    {
        return -1;
    }

    if (queue->head == NULL)
    {
        return -1;
    }

    node_t *ptr = queue->head;
    const int value = ptr->value;

    queue->size--;
    queue->head = queue->head->next;
    if (queue->head)
    {
        queue->head->prev = NULL;
    }

    if (queue->tail == ptr)
    {
        queue->tail = NULL;
    }

    free(ptr);

    return value;
}

int double_ended_queue_pop_tail(double_ended_queue_t *queue)
{
    if (queue == NULL)
    {
        return -1;
    }

    if (queue->tail == NULL)
    {
        return -1;
    }

    node_t *ptr = queue->tail;
    const int value = ptr->value;

    queue->size--;
    queue->tail = queue->tail->prev;
    if (queue->tail)
    {
        queue->tail->next = NULL;
    }

    if (queue->head == ptr)
    {
        queue->head = NULL;
    }

    free(ptr);

    return value;
}

size_t double_ended_queue_size(double_ended_queue_t *queue)
{
    if (queue == NULL)
    {
        return 0;
    }

    return queue->size;
}
