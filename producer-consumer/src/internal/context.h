#pragma once

#include <pthread.h>
#include <stdatomic.h>


typedef struct
{
    atomic_int state;
    pthread_t  pthread;
} context_t;
