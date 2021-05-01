#include <signal/signal.h>
#include <consumer/consumer.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void* worker_loop(void* args)
{
    if (!args)
    {
        fprintf(stderr, "worker context is NULL in `worker` thread\n");
        exit(ERR_PTRNULL);
    }

    worker_t *worker = (worker_t *)args;
    srand(time(0));

    signal_block();

    while (worker->context.state != STATE_STOP)
    {
        if (worker->context.state == STATE_RUN)
        {
            pthread_mutex_lock(&(worker->mutex));
            printf("process task, value %d\n", worker->task->data);
            free(worker->task);
            worker->task = NULL;
            pthread_mutex_unlock(&(worker->mutex));
            sleep(rand() % 3);
            worker->statistic_counter++;

            if (worker->context.state != STATE_STOP)
            {
                worker->context.state = STATE_IDLE;
            }
        }
        sleep(1);
    }

    return NULL;
}

consumer_t *consumer_create(const size_t size)
{
    consumer_t *ptr = (consumer_t *)calloc(1, sizeof(consumer_t));
    if (!ptr)
    {
        fprintf(stderr, "can't allocate memory for `consumer`\n");
        return NULL;
    }

    ptr->workers = (worker_t *)calloc(size, sizeof(worker_t));
    if (!ptr->workers)
    {
        fprintf(stderr, "can't allocate memory for `workers`\n");
        free(ptr);
        return NULL;
    }

    ptr->size = size;
    ptr->state = STATE_INIT;

    return ptr;
}

void consumer_destroy(consumer_t **consumer)
{
    consumer_t *ptr = *consumer;
    if (!ptr)
    {
        return;
    }

    printf("shutdown `consumer` ...\n");

    if (ptr->state == STATE_RUN)
    {
        for (size_t i = 0; i < ptr->size; ++i)
        {
            if (pthread_cancel(ptr->workers[i].context.pthread) != 0)
            {
                fprintf(stderr, "can't cancel thread %ld for `consumer`\n", i);
            }
            if (pthread_join(ptr->workers[i].context.pthread, NULL) != 0)
            {
                fprintf(stderr, "can't join thread %ld for `consumer`\n", i);
            }
            if (pthread_mutex_destroy(&ptr->workers[i].mutex) != 0)
            {
                fprintf(stderr, "can't destroy mutex thread %ld for `consumer`\n", i);
            }
        }
    }

    for (size_t i = 0; i < ptr->size; ++i)
    {
        free(ptr->workers[i].task);
    }

    free(ptr->workers);
    free(ptr);
    *consumer = NULL;
}

err_code_e consumer_run(consumer_t *ptr)
{
    if (!ptr)
    {
        fprintf(stderr, "can't run `consumer`, `consumer` ptr is NULL\n");
        return ERR_PTRNULL;
    }
    if (ptr->state != STATE_INIT)
    {
        fprintf(stderr, "can't run `consumer`, is not initialized\n");
        return ERR_INTERNAL;
    }

    for (size_t i = 0; i < ptr->size; ++i)
    {
        ptr->workers[i].context.state = STATE_IDLE;
        if (pthread_mutex_init(&(ptr->workers[i].mutex), NULL) != 0)
        {
            fprintf(stderr, "can't init mutex thread %ld for `consumer`\n", i);
            return ERR_INTERNAL;
        }
        if (pthread_create(&(ptr->workers[i].context.pthread), NULL, &worker_loop, &(ptr->workers[i])) != 0)
        {
            fprintf(stderr, "can't create thread %ld for `consumer`\n", i);
            return ERR_INTERNAL;
        }
    }

    ptr->state = STATE_RUN;

    return ERR_NONE;
}

void consumer_stop(consumer_t *ptr)
{
    if (!ptr)
    {
        return;
    }
    if (ptr->state != STATE_RUN)
    {
        return;
    }

    printf("stop `consumer` ...\n");

    ptr->state = STATE_STOP;
    for (size_t i = 0; i < ptr->size; ++i)
    {
        ptr->workers[i].context.state = STATE_STOP;
        if (pthread_join(ptr->workers[i].context.pthread, NULL) != 0)
        {
            fprintf(stderr, "can't join thread %ld for `consumer`\n", i);
        }
    }
}

err_code_e consumer_add_worker_task(consumer_t *ptr, size_t worker_idx, task_t *task)
{
    if (!ptr)
    {
        fprintf(stderr, "can't add worker task, consumer ptr is NULL\n");
        return ERR_PTRNULL;
    }
    if (ptr->size < worker_idx)
    {
        fprintf(stderr, "can't add worker task, no space\n");
        return ERR_INTERNAL;
    }
    if (!task)
    {
        fprintf(stderr, "can't add worker task, task ptr is NULL\n");
        return ERR_PTRNULL;
    }

    worker_t *w = &(ptr->workers[worker_idx]);

    pthread_mutex_lock(&(w->mutex));
    w->task = task;
    pthread_mutex_unlock(&(w->mutex));
    w->context.state = STATE_RUN;

    return ERR_NONE;
}

state_e consumer_get_worker_state(consumer_t *ptr, size_t worker_idx)
{
    if (!ptr)
    {
        fprintf(stderr, "can't get worker state, consumer ptr is NULL\n");
        return ERR_PTRNULL;
    }
    if (ptr->size < worker_idx)
    {
        fprintf(stderr, "can't get worker state, invalid worker index\n");
        return ERR_INTERNAL;
    }

    return ptr->workers[worker_idx].context.state;
}

err_code_e consumer_print_statistic(consumer_t *ptr)
{
    if (!ptr)
    {
        fprintf(stderr, "can't print statistic, consumer ptr is NULL\n");
        return ERR_PTRNULL;
    }

    printf("\n+++++++++++++++++++++++++++\n");
    for (size_t i = 0; i < ptr->size; ++i)
    {
        printf("+ worker %ld done %d tasks\n", i, ptr->workers[i].statistic_counter);
    }
    printf("+++++++++++++++++++++++++++\n");

    return ERR_NONE;
}
