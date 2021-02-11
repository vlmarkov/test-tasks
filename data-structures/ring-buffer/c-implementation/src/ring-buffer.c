#include <stdio.h>

#include <ring-buffer.h>


static void internal_safe_move_ptr_(ring_buffer_t *ring_buffer, node_t **ptr)
{
    if (ring_buffer == NULL)
    {
        return;
    }

    if (*ptr == NULL)
    {
        return;
    }

    if (*ptr == ring_buffer->last_node)
    {
        *ptr = ring_buffer->buffer; // Go to the begining
    }
    else
    {
        *ptr += 1;
    }
}

ring_buffer_t *ring_buffer_create(const size_t size)
{
    ring_buffer_t *new = calloc(sizeof(ring_buffer_t), 1);
    if (new == NULL)
    {
        return NULL;
    }

    new->buffer = calloc(sizeof(node_t), size);
    if (new->buffer == NULL)
    {
        ring_buffer_destroy(&new);
        return NULL;
    }

    new->size = size;
    new->last_node = new->buffer + size - 1;
    new->head = new->buffer;
    new->tail = new->buffer;
    new->catch_up = false;

    for (size_t i = 0; i < new->size; ++i)
    {
        new->buffer[i].value = -1;
    }

    return new;
}

void ring_buffer_destroy(ring_buffer_t **ring_buffer)
{
    if (*ring_buffer)
    {
        ring_buffer_t *ptr = *ring_buffer;
        if (ptr->buffer)
        {
            free(ptr->buffer);
        }
        free(ptr);
        *ring_buffer = NULL;
    }
}

void ring_buffer_push(ring_buffer_t *ring_buffer, int value)
{
    if (ring_buffer == NULL)
    {
        return;
    }

    if (ring_buffer->catch_up)
    {
        ring_buffer->catch_up = false;
        internal_safe_move_ptr_(ring_buffer, &ring_buffer->tail);
    }

    ring_buffer->head->value = value;

    internal_safe_move_ptr_(ring_buffer, &ring_buffer->head);
    if (ring_buffer->head == ring_buffer->tail)
    {
        ring_buffer->catch_up = true;
    }
}

int ring_buffer_pop(ring_buffer_t *ring_buffer)
{
    if (ring_buffer == NULL)
    {
        return -1;
    }

    int value = ring_buffer->tail->value;
    ring_buffer->tail->value = -1;

    if (ring_buffer->tail == ring_buffer->head && ring_buffer->catch_up)
    {
        ring_buffer->catch_up = false;
        internal_safe_move_ptr_(ring_buffer, &ring_buffer->tail);
    }
    else if (ring_buffer->tail != ring_buffer->head)
    {
        internal_safe_move_ptr_(ring_buffer, &ring_buffer->tail);
    }

    return value;
}

void ring_buffer_print(ring_buffer_t *ring_buffer)
{
    if (ring_buffer == NULL)
    {
        return;
    }

    printf("[RING BUFFER PRINT]: size : %lu\n", ring_buffer->size);

    for (size_t i = 0; i < ring_buffer->size; ++i)
    {
        if (ring_buffer->tail == &ring_buffer->buffer[i] &&
            ring_buffer->head == &ring_buffer->buffer[i])
        {
            printf("[RING BUFFER PRINT]: node[%lu]:value[%d]\t<- H T\n",
                i, ring_buffer->buffer[i].value);
        }
        else if (ring_buffer->head == &ring_buffer->buffer[i])
        {
            printf("[RING BUFFER PRINT]: node[%lu]:value[%d]\t<- H\n", i,
                ring_buffer->buffer[i].value);
        }
        else if (ring_buffer->tail == & ring_buffer->buffer[i])
        {
            printf("[RING BUFFER PRINT]: node[%lu]:value[%d]\t<- T\n", i,
                ring_buffer->buffer[i].value);
        }
        else
        {
            printf("[RING BUFFER PRINT]: node[%lu]:value[%d]\n",
                i, ring_buffer->buffer[i].value);
        }
    }
}
