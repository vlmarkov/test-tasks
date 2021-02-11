#include <ring-buffer.h>


int main(int argc, char const *argv[])
{
    ring_buffer_t *ring_buffer = ring_buffer_create(10);
    if (ring_buffer == NULL)
    {
        return -1;
    }

    ring_buffer_print(ring_buffer);

    ring_buffer_push(ring_buffer, 0);
    ring_buffer_print(ring_buffer);

    ring_buffer_pop(ring_buffer);
    ring_buffer_print(ring_buffer);

    ring_buffer_destroy(&ring_buffer);

    return 0;
}
