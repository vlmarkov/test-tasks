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
    node_t *tail;
    size_t size;
} double_ended_queue_t;

double_ended_queue_t *double_ended_queue_create();
void double_ended_queue_destroy(double_ended_queue_t **queue);
void double_ended_queue_print(double_ended_queue_t *queue);
void double_ended_queue_push_top(double_ended_queue_t *queue, const int value);
void double_ended_queue_push_tail(double_ended_queue_t *queue, const int value);
int double_ended_queue_pop_top(double_ended_queue_t *queue);
int double_ended_queue_pop_tail(double_ended_queue_t *queue);
size_t double_ended_queue_size(double_ended_queue_t *queue);
