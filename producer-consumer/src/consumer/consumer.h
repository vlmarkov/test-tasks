#pragma once

#include <internal/task.h>
#include <internal/state.h>
#include <internal/errors.h>

#include <stddef.h>
#include <pthread.h>
#include <stdatomic.h>


typedef struct
{
    atomic_int       state;
    pthread_t        pthread;
    atomic_int       statistic;
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
void consumer_destroy(consumer_t **consumer);

err_code_e consumer_init(consumer_t *consumer, const size_t size);

err_code_e consumer_run(consumer_t *consumer);
void consumer_stop(consumer_t *consumer);

err_code_e consumer_add_worker_task(consumer_t *consumer, size_t worker, task_t *task);
state_e consumer_get_worker_state(consumer_t *consumer, size_t worker);

err_code_e consumer_print_statistic(consumer_t *consumer);