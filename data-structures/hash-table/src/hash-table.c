#include <stdio.h>

#include <hash-table.h>


static int internal_hash_(const int value)
{
    return value;
}

hash_table_t *hash_table_create(size_t size)
{
    hash_table_t *new = calloc(sizeof(hash_table_t), 1);
    if (new == NULL)
    {
        return NULL;
    }

    new->table = calloc(sizeof(node_t), size);
    if (new->table == NULL)
    {
        hash_table_destroy(&new);
        return NULL;
    }

    new->size = size;
    new->capacity = 0;

    for (int i = 0; i < new->size; ++i)
    {
        new->table[i].value = -1;
    }

    return new;
}

void hash_table_destroy(hash_table_t **ptr)
{
    if (*ptr)
    {
        hash_table_t *hash_table = *ptr;
        free(hash_table->table);
        *ptr = NULL;
    }
}

void hash_table_print(hash_table_t *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    printf("[HASH TABLE PRINT]: size     : %lu\n", ptr->size);
    printf("[HASH TABLE PRINT]: capacity : %lu\n", ptr->capacity);

    for (int i = 0; i < ptr->size; ++i)
    {
        printf("[HASH TABLE PRINT]: value[%d]\n", ptr->table[i].value);
    }
}

int hash_table_add(hash_table_t *ptr, const int value)
{
    if (ptr == NULL)
    {
        return -1;
    }

    if (ptr->capacity == ptr->size)
    {
        return -1;
    }

    node_t *node = ptr->table + (internal_hash_(value) % ptr->size);
    if (node->value != -1)
    {
        return -1;
    }

    node->value = value;
    ptr->capacity++;

    return 0;
}

int hash_table_delete(hash_table_t *ptr, const int value)
{
    if (ptr == NULL)
    {
        return -1;
    }

    ptr->capacity--;
    ptr->table[internal_hash_(value) % ptr->size].value = -1;

    return 0;
}

int hash_table_search(hash_table_t *ptr, const int value)
{
    if (ptr == NULL)
    {
        return -1;
    }

    return ptr->table[internal_hash_(value) % ptr->size].value;
}

int hash_table_size(hash_table_t *ptr)
{
    if (ptr == NULL)
    {
        return -1;
    }

    return ptr->size;
}

int hash_table_capacity(hash_table_t *ptr)
{
    if (ptr == NULL)
    {
        return -1;
    }

    return ptr->capacity;
}
