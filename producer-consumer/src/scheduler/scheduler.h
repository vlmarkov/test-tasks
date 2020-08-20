#pragma once

#include <internal/task.h>
#include <internal/errors.h>
#include <internal/context.h>
#include <consumer/consumer.h>


typedef struct
{
    pthread_mutex_t   mutex;
    size_t            size;
    size_t            next_idx; // MUST BE PROTECTED
    task_t          **tasks;    // MUST BE PROTECTED
} storage_t;

typedef struct
{
    context_t   context;
    storage_t   storage;
    consumer_t *consumer;
} scheduler_t;

scheduler_t *scheduler_create();
void scheduler_destroy(scheduler_t **ptr);

err_code_e scheduler_run(scheduler_t *ptr);
void scheduler_stop(scheduler_t *ptr);

err_code_e scheduler_add(scheduler_t *ptr, task_t *task);
