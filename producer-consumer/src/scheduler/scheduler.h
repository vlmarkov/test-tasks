#pragma once

#include <consumer/consumer.h>
#include <internal/errors.h>
#include <internal/task.h>

#include <pthread.h>
#include <stdatomic.h>


typedef struct
{
    atomic_int        state;
    pthread_t         pthread;
    consumer_t       *consumer;
    size_t            size;
    pthread_mutex_t   mutex;
    task_t          **tasks; // MUST BE PROTECTED
    size_t            head;  // MUST BE PROTECTED
} scheduler_t;

scheduler_t *scheduler_create();
void scheduler_destroy(scheduler_t **scheduler);

err_code_e scheduler_init(scheduler_t *scheduler, consumer_t *consumer);

err_code_e scheduler_run(scheduler_t *scheduler);
void scheduler_stop(scheduler_t *scheduler);

err_code_e scheduler_add(scheduler_t *scheduler, task_t *task);
