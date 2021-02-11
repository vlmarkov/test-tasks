#include <hash-table.h>


int main(int argc, char const *argv[])
{
    hash_table_t *ptr = hash_table_create(10);
    if (ptr == NULL)
    {
        return -1;
    }

    hash_table_print(ptr);

    hash_table_add(ptr, 5);
    hash_table_print(ptr);
    hash_table_search(ptr, 5);
    hash_table_delete(ptr, 5);
    hash_table_print(ptr);

    hash_table_destroy(&ptr);
    return 0;
}
