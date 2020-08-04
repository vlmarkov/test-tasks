#include <producer/producer.h>
#include <signal/signal.h>
#include <internal/state.h>
#include <internal/task.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h> 


static void* producer_loop(void* args)
{
    if (!args)
    {
        // TODO: error message
        exit(ERR_PTRNULL);
    }

    signal_block();

    producer_t *producer = (producer_t *)args;
    srand(time(0));

    while (producer->state == STATE_RUN)
    {
        int rand_sleep = rand() % 2; // 0 to 2 seconds

        task_t *task = (task_t*)calloc(1, sizeof(task_t));
        if (!task)
        {
            // TODO: error message
            exit(ERR_MEMORY);
        }

        task->data = rand_sleep;
        scheduler_add(producer->scheduler, task);

        sleep(rand_sleep);
    }
}

producer_t *producer_create()
{
    printf("%s(): invoke\n", __func__);

    producer_t * producer = (producer_t *)calloc(1, sizeof(producer_t));

    printf("%s(): done\n", __func__);
    return producer;
}

err_code_e producer_destroy(producer_t **producer)
{
    printf("%s(): invoke\n", __func__);

    if (!*producer)
    {
        return ERR_PTRNULL;
    }

    if ((*producer)->state == STATE_RUN)
    {
        pthread_cancel((*producer)->pthread); // TODO: error check
        pthread_join((*producer)->pthread, NULL); // TODO: error check
    }

    free(*producer);
    *producer = NULL;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e producer_init(producer_t *producer, scheduler_t *scheduler)
{
    printf("%s(): invoke\n", __func__);

    if (!producer)
    {
        return ERR_PTRNULL;
    }
    if (!scheduler)
    {
        return ERR_PTRNULL;
    }

    producer->scheduler = scheduler;
    producer->state = STATE_INIT;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e producer_run(producer_t *producer)
{
    printf("%s(): invoke\n", __func__);

    if (!producer)
    {
        return ERR_PTRNULL;
    }
    if (producer->state != STATE_INIT)
    {
        return ERR_INTERNAL;
    }

    if (pthread_create(&producer->pthread, NULL, &producer_loop, producer) != 0)
    {
        return ERR_INTERNAL;
    }

    producer->state = STATE_RUN;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e producer_stop(producer_t *producer)
{
    printf("%s(): invoke\n", __func__);

    if (!producer)
    {
        return ERR_PTRNULL;
    }
    if (producer->state != STATE_RUN)
    {
        return ERR_INTERNAL;
    }

    producer->state = STATE_STOP;
    pthread_join(producer->pthread, NULL); // TODO: error check

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}