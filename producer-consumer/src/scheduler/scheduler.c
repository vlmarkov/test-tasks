#include <scheduler/scheduler.h>
#include <internal/state.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal/signal.h>
#include <signal.h>


static err_code_e scheduler_process(scheduler_t *scheduler)
{
    printf("%s(): invoke\n", __func__);

    pthread_mutex_lock(&(scheduler->mutex));
    if (scheduler->head == 0)
    {
        pthread_mutex_unlock(&(scheduler->mutex));
        printf("%s(): done\n", __func__);
        return ERR_NONE;
    }

    for (size_t i = 0; i < scheduler->consumer->size; ++i)
    {
        if (consumer_get_worker_state(scheduler->consumer, i) == STATE_IDLE && scheduler->head > 0)
        {
            task_t *task = scheduler->tasks[scheduler->head - 1];
            printf("%s(): task = %d\n", __func__, task->data);
            if (consumer_add_worker_task(scheduler->consumer, i, task) == ERR_NONE)
            {
                scheduler->tasks[scheduler->head - 1] = NULL;
                scheduler->head--;
            }
        }
    }

    pthread_mutex_unlock(&(scheduler->mutex));

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

static void* scheduler_loop(void* args)
{
    if (!args)
    {
        // TODO: error message
        exit(ERR_PTRNULL);
    }

    signal_block();

    scheduler_t *scheduler = (scheduler_t *)args;

    while (scheduler->state == STATE_RUN)
    {
        if (scheduler_process(scheduler) != ERR_NONE)
        {
            // TODO: error message
            exit(ERR_INTERNAL);
        }
        sleep(1);
    }
}

scheduler_t *scheduler_create()
{
    printf("%s(): invoke\n", __func__);

    scheduler_t *scheduler = (scheduler_t *)calloc(1, sizeof(scheduler_t));

    printf("%s(): done\n", __func__);
    return scheduler;
}

err_code_e scheduler_destroy(scheduler_t **scheduler)
{
    printf("%s(): invoke\n", __func__);

    if (!*scheduler)
    {
        return ERR_PTRNULL;
    }

    if ((*scheduler)->state == STATE_RUN)
    {
        pthread_cancel((*scheduler)->pthread); // TODO: error check
        pthread_join((*scheduler)->pthread, NULL); // TODO: error check
    }

    pthread_mutex_destroy(&(*scheduler)->mutex); // TODO: error check

    for (size_t i = 0; i < (*scheduler)->size; ++i)
    {
        free((*scheduler)->tasks[i]);
        (*scheduler)->tasks[i] = NULL;
    }

    free((*scheduler)->tasks);
    free(*scheduler);
    *scheduler = NULL;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e scheduler_init(scheduler_t *scheduler, consumer_t *consumer)
{
    printf("%s(): invoke\n", __func__);

    if (!scheduler)
    {
        return ERR_PTRNULL;
    }
    if (!consumer)
    {
        return ERR_PTRNULL;
    }

    pthread_mutex_init(&(scheduler->mutex), NULL); // TODO: error check
    scheduler->consumer = consumer;
    scheduler->state = STATE_INIT;

    scheduler->size = 100;
    scheduler->head = 0;
    scheduler->tasks = (task_t **)calloc(100, sizeof(task_t*));
    if (!scheduler->tasks)
    {
        return ERR_MEMORY;
    }

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e scheduler_run(scheduler_t *scheduler)
{
    printf("%s(): invoke\n", __func__);

    if (!scheduler)
    {
        return ERR_PTRNULL;
    }

    if (pthread_create(&scheduler->pthread, NULL, &scheduler_loop, scheduler) != 0)
    {
        return ERR_INTERNAL;
    }

    scheduler->state = STATE_RUN;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e scheduler_stop(scheduler_t *scheduler)
{
    printf("%s(): invoke\n", __func__);

    if (!scheduler)
    {
        return ERR_PTRNULL;
    }
    if (scheduler->state != STATE_RUN)
    {
        return ERR_INTERNAL;
    }

    scheduler->state = STATE_STOP;
    pthread_join(scheduler->pthread, NULL); // TODO: error check

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e scheduler_add(scheduler_t *scheduler, task_t *task)
{
    printf("%s(): invoke\n", __func__);

    if (!scheduler)
    {
        return ERR_PTRNULL;
    }
    if (!task)
    {
        return ERR_PTRNULL;
    }
    if (scheduler->state != STATE_RUN)
    {
        return ERR_INTERNAL;
    }

    err_code_e rc = ERR_MEMORY;

    pthread_mutex_lock(&(scheduler->mutex));
    if (scheduler->head < scheduler->size)
    {
        scheduler->tasks[scheduler->head] = task;
        printf("%s(): tasks[%ld] = %d\n", __func__,
            scheduler->head, scheduler->tasks[scheduler->head]->data);
        scheduler->head++;
        rc = ERR_NONE;
    }
    pthread_mutex_unlock(&(scheduler->mutex));

    printf("%s(): done\n", __func__);
    return rc;
}
