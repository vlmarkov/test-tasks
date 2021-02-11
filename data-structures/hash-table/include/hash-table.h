#pragma once

#include <stdlib.h>


typedef struct
{
    int value;
} node_t;

typedef struct
{
    node_t *table;
    size_t size;
    size_t capacity;
} hash_table_t;

hash_table_t *hash_table_create(size_t size);
void hash_table_destroy(hash_table_t **ptr);
void hash_table_print(hash_table_t *ptr);
int hash_table_add(hash_table_t *ptr, const int value);
int hash_table_delete(hash_table_t *ptr, const int value);
int hash_table_search(hash_table_t *ptr, const int value);
int hash_table_size(hash_table_t *ptr);
int hash_table_capacity(hash_table_t *ptr);
