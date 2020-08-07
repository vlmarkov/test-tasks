#pragma once

#include <internal/errors.h>
#include <internal/context.h>
#include <scheduler/scheduler.h>


typedef struct
{
    context_t    context;
    scheduler_t *scheduler;
} producer_t;

producer_t *producer_create();
void producer_destroy(producer_t **ptr);

err_code_e producer_run(producer_t *ptr);
void producer_stop(producer_t *ptr);
