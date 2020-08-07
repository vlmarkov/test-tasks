#include <internal/task.h>
#include <signal/signal.h>
#include <internal/state.h>
#include <producer/producer.h>

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void* producer_loop(void* args)
{
    if (!args)
    {
        fprintf(stderr, "producer context is NULL in `producer` thread\n");
        exit(ERR_PTRNULL);
    }

    signal_block();

    producer_t *producer = (producer_t *)args;
    srand(time(0));

    while (producer->context.state == STATE_RUN)
    {
        int rand_sleep = rand() % 2; // 0 to 2 seconds

        task_t *task = (task_t*)calloc(1, sizeof(task_t));
        if (!task)
        {
            fprintf(stderr, "`producer` can't create task\n");
            exit(ERR_MEMORY);
        }

        task->data = rand_sleep;
        if (scheduler_add(producer->scheduler, task) != ERR_NONE)
        {
            free(task);
        }

        sleep(rand_sleep);
    }

    return NULL;
}

producer_t *producer_create(scheduler_t *scheduler)
{
    if (!scheduler)
    {
        fprintf(stderr, "ptr `scheduler` is NULL\n");
        return NULL;
    }

    producer_t *ptr = (producer_t *)calloc(1, sizeof(producer_t));
    if (!ptr)
    {
        fprintf(stderr, "can't allocate memory for `producer`\n");
        return NULL;
    }

    ptr->scheduler = scheduler;
    ptr->context.state = STATE_INIT;

    return ptr;
}

void producer_destroy(producer_t **producer)
{
    producer_t *ptr = *producer;
    if (!ptr)
    {
        return;
    }

    printf("shutdown `producer` ...\n");

    if (ptr->context.state == STATE_RUN)
    {
        if (pthread_cancel(ptr->context.pthread) != 0)
        {
            fprintf(stderr, "can't cancel `producer` thread\n");
        }
        if (pthread_join(ptr->context.pthread, NULL) != 0)
        {
            fprintf(stderr, "can't join `producer` thread\n");
        }
    }

    free(ptr);
    *producer = NULL;
}

err_code_e producer_run(producer_t *ptr)
{
    if (!ptr)
    {
        fprintf(stderr, "`producer` ptr is NULL\n");
        return ERR_PTRNULL;
    }
    if (ptr->context.state != STATE_INIT)
    {
        fprintf(stderr, "`producer` is not initialized\n");
        return ERR_INTERNAL;
    }

    if (pthread_create(&ptr->context.pthread, NULL, &producer_loop, ptr) != 0)
    {
        fprintf(stderr, "can't create `producer` thread\n");
        return ERR_INTERNAL;
    }

    ptr->context.state = STATE_RUN;

    return ERR_NONE;
}

void producer_stop(producer_t *ptr)
{
    if (!ptr)
    {
        return;
    }
    if (ptr->context.state != STATE_RUN)
    {
        return;
    }

    printf("stop `producer` ...\n");

    ptr->context.state = STATE_STOP;
    if (pthread_join(ptr->context.pthread, NULL) != 0)
    {
        fprintf(stderr, "can't join `producer` thread\n");
    }
}
