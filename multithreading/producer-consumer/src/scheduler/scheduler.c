#include <signal/signal.h>
#include <internal/state.h>
#include <scheduler/scheduler.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static err_code_e scheduler_process(scheduler_t *ptr)
{
    pthread_mutex_lock(&(ptr->storage.mutex));
    if (ptr->storage.next_idx == 0)
    {
        pthread_mutex_unlock(&(ptr->storage.mutex));
        return ERR_NONE;
    }

    for (size_t i = 0; i < ptr->consumer->size; ++i)
    {
        if (consumer_get_worker_state(ptr->consumer, i) == STATE_IDLE && ptr->storage.next_idx > 0)
        {
            task_t *task = ptr->storage.tasks[ptr->storage.next_idx - 1];
            printf("assign task = %d to worker %ld\n", task->data, i);
            if (consumer_add_worker_task(ptr->consumer, i, task) == ERR_NONE)
            {
                ptr->storage.tasks[ptr->storage.next_idx - 1] = NULL;
                ptr->storage.next_idx--;
            }
        }
    }

    pthread_mutex_unlock(&(ptr->storage.mutex));
    return ERR_NONE;
}

static void* scheduler_loop(void* args)
{
    if (!args)
    {
        fprintf(stderr, "scheduler context is NULL in `scheduler` thread\n");
        exit(ERR_PTRNULL);
    }

    signal_block();

    scheduler_t *ptr = (scheduler_t *)args;

    while (ptr->context.state == STATE_RUN)
    {
        if (scheduler_process(ptr) != ERR_NONE)
        {
            fprintf(stderr, "scheduler process error\n");
            exit(ERR_INTERNAL);
        }
        sleep(1);
    }

    return NULL;
}

scheduler_t *scheduler_create(consumer_t *consumer)
{
    if (!consumer)
    {
        fprintf(stderr, "ptr `consumer` is NULL\n");
        return NULL;
    }

    scheduler_t *ptr = (scheduler_t *)calloc(1, sizeof(scheduler_t));
    if (!ptr)
    {
        fprintf(stderr, "can't allocate memory for `scheduler`\n");
        return NULL;
    }

    ptr->storage.size = 100; // Default tasks storage size
    ptr->storage.next_idx = 0;
    ptr->storage.tasks = (task_t **)calloc(ptr->storage.size, sizeof(task_t*));
    if (!ptr->storage.tasks)
    {
        fprintf(stderr, "can't allocate memory for `tasks`");
        free(ptr);
        return NULL;
    }

    if (pthread_mutex_init(&(ptr->storage.mutex), NULL) != 0)
    {
        fprintf(stderr, "can't init mutex `scheduler` thread\n");
        free(ptr);
        return NULL;
    }
    ptr->consumer = consumer;
    ptr->context.state = STATE_INIT;

    return ptr;
}

void scheduler_destroy(scheduler_t **scheduler)
{
    scheduler_t *ptr = *scheduler;
    if (!ptr)
    {
        return;
    }

    printf("shutdown `scheduler` ...\n");

    if (ptr->context.state == STATE_RUN)
    {
        if (pthread_cancel(ptr->context.pthread) != 0)
        {
            fprintf(stderr, "can't cancel `scheduler` thread\n");
        }
        if (pthread_join(ptr->context.pthread, NULL) != 0)
        {
            fprintf(stderr, "can't join`scheduler` thread\n");
        }
        if (pthread_mutex_destroy(&ptr->storage.mutex) != 0)
        {
            fprintf(stderr, "can't destroy mutex `scheduler` thread\n");
        }
    }

    for (size_t i = 0; i < ptr->storage.size; ++i)
    {
        free(ptr->storage.tasks[i]);
        ptr->storage.tasks[i] = NULL;
    }

    free(ptr->storage.tasks);
    free(ptr);
    *scheduler = NULL;
}

err_code_e scheduler_run(scheduler_t *ptr)
{
    if (!ptr)
    {
        fprintf(stderr, "`scheduler` ptr is NULL\n");
        return ERR_PTRNULL;
    }

    if (pthread_create(&ptr->context.pthread, NULL, &scheduler_loop, ptr) != 0)
    {
        fprintf(stderr, "can't create `scheduler` thread\n");
        return ERR_INTERNAL;
    }

    ptr->context.state = STATE_RUN;

    return ERR_NONE;
}

void scheduler_stop(scheduler_t *ptr)
{
    if (!ptr)
    {
        return;
    }
    if (ptr->context.state != STATE_RUN)
    {
        return;
    }

    printf("stop `scheduler` ...\n");

    ptr->context.state = STATE_STOP;
    if (pthread_join(ptr->context.pthread, NULL) != 0)
    {
        fprintf(stderr, "can't join thread for `scheduler`\n");
    }
}

err_code_e scheduler_add(scheduler_t *ptr, task_t *task)
{
    if (!ptr)
    {
        return ERR_PTRNULL;
    }
    if (ptr->context.state != STATE_RUN)
    {
        return ERR_INTERNAL;
    }
    if (!task)
    {
        return ERR_PTRNULL;
    }

    err_code_e rc = ERR_MEMORY;

    pthread_mutex_lock(&(ptr->storage.mutex));
    if (ptr->storage.next_idx < ptr->storage.size)
    {
        ptr->storage.tasks[ptr->storage.next_idx] = task;
        printf("store tasks %ld with value %d\n", 
            ptr->storage.next_idx, ptr->storage.tasks[ptr->storage.next_idx]->data);
        ptr->storage.next_idx++;
        rc = ERR_NONE;
    }
    pthread_mutex_unlock(&(ptr->storage.mutex));

    return rc;
}
