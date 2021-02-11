#include <queue.h>


int main(int argc, char const *argv[])
{
    {
        double_ended_queue_t *queue = double_ended_queue_create();
        if (queue == NULL)
        {
            return -1;
        }

        double_ended_queue_print(queue);

        double_ended_queue_push_top(queue, 5);
        double_ended_queue_print(queue);
        double_ended_queue_push_top(queue, 10);
        double_ended_queue_print(queue);
        double_ended_queue_push_top(queue, 15);
        double_ended_queue_print(queue);

        double_ended_queue_pop_top(queue);
        double_ended_queue_print(queue);

        double_ended_queue_destroy(&queue);
    }

    {
        double_ended_queue_t *queue = double_ended_queue_create();
        if (queue == NULL)
        {
            return -1;
        }

        double_ended_queue_print(queue);

        double_ended_queue_push_tail(queue, 5);
        double_ended_queue_print(queue);
        double_ended_queue_push_tail(queue, 10);
        double_ended_queue_print(queue);
        double_ended_queue_push_tail(queue, 15);
        double_ended_queue_print(queue);

        double_ended_queue_pop_tail(queue);
        double_ended_queue_print(queue);

        double_ended_queue_destroy(&queue);
    }

    {
        double_ended_queue_t *queue = double_ended_queue_create();
        if (queue == NULL)
        {
            return -1;
        }

        double_ended_queue_print(queue);

        double_ended_queue_push_top(queue, 0);
        double_ended_queue_print(queue);
        double_ended_queue_push_tail(queue, 5);
        double_ended_queue_print(queue);
        double_ended_queue_push_top(queue, -5);
        double_ended_queue_print(queue);

        double_ended_queue_pop_tail(queue);
        double_ended_queue_print(queue);

        double_ended_queue_pop_top(queue);
        double_ended_queue_print(queue);

        double_ended_queue_destroy(&queue);
    }

    return 0;
}
