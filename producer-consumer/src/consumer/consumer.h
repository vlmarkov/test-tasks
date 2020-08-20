#pragma once

#include <internal/task.h>
#include <internal/state.h>
#include <internal/errors.h>
#include <internal/context.h>


typedef struct
{
    context_t        context;
    atomic_int       statistic_counter;
    pthread_mutex_t  mutex;
    task_t          *task;
} worker_t;

typedef struct
{
    atomic_int state;
    size_t     size;
    worker_t   *workers;
} consumer_t;

consumer_t *consumer_create();
void consumer_destroy(consumer_t **ptr);

err_code_e consumer_run(consumer_t *ptr);
void consumer_stop(consumer_t *ptr);

err_code_e consumer_add_worker_task(consumer_t *ptr, size_t worker_idx, task_t *task);
state_e consumer_get_worker_state(consumer_t *ptr, size_t worker_idx);

err_code_e consumer_print_statistic(consumer_t *ptr);
