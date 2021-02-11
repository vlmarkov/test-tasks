#pragma once

#include <stdlib.h>
#include <stdbool.h>


typedef struct
{
    int value;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
    node_t *buffer;
    node_t *last_node;
    size_t size;
    bool catch_up;
} ring_buffer_t;

ring_buffer_t *ring_buffer_create(const size_t size);
void ring_buffer_destroy(ring_buffer_t **ring_buffer);
void ring_buffer_print(ring_buffer_t *ring_buffer);
void ring_buffer_push(ring_buffer_t *ring_buffer, const int value);
int ring_buffer_pop(ring_buffer_t *ring_buffer);
