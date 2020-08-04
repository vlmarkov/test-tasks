#pragma once

#include <scheduler/scheduler.h>
#include <internal/errors.h>

#include <pthread.h>
#include <stdatomic.h>


typedef struct
{
    atomic_int   state;
    pthread_t    pthread;
    scheduler_t *scheduler;
} producer_t;


producer_t *producer_create();
err_code_e producer_destroy(producer_t **producer);

err_code_e producer_init(producer_t *producer, scheduler_t *scheduler);

err_code_e producer_run(producer_t *producer);
err_code_e producer_stop(producer_t *producer);
