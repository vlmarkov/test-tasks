#include <consumer/consumer.h>
#include <internal/state.h>
#include <signal/signal.h>

#include <stdlib.h>


static void* worker_loop(void* args)
{
    if (!args)
    {
        // TODO: error message
        exit(ERR_PTRNULL);
    }

    worker_t *worker = (worker_t *)args;
    srand(time(0));

    signal_block();

    while (worker->state != STATE_STOP)
    {
        if (worker->state == STATE_RUN)
        {
            pthread_mutex_lock(&(worker->mutex));
            printf(" > consumer->worker thread = %d\n", worker->task->data);
            free(worker->task);
            worker->task = NULL;
            pthread_mutex_unlock(&(worker->mutex));
            sleep(rand() % 3);
            worker->statistic++;

            if (worker->state != STATE_STOP)
            {
                worker->state = STATE_IDLE;
            }
        }
        sleep(1);
    }
}

consumer_t *consumer_create()
{
    printf("%s(): invoke\n", __func__);

    consumer_t *consumer = (consumer_t *)calloc(1, sizeof(consumer_t));

    printf("%s(): done\n", __func__);
    return consumer;
}

err_code_e consumer_destroy(consumer_t **consumer)
{
    printf("%s(): invoke\n", __func__);

    if (!*consumer)
    {
        return ERR_PTRNULL;
    }

    if ((*consumer)->state == STATE_RUN)
    {
        for (size_t i = 0; i < (*consumer)->size; ++i)
        {
            pthread_cancel((*consumer)->workers[i].pthread);       // TODO: error check
            pthread_join((*consumer)->workers[i].pthread, NULL);   // TODO: error check
            pthread_mutex_destroy(&(*consumer)->workers[i].mutex); // TODO: error check
        }
    }

    free((*consumer)->workers);
    free(*consumer);
    *consumer = NULL;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e consumer_init(consumer_t *consumer, const size_t size)
{
    printf("%s(): invoke\n", __func__);

    if (!consumer)
    {
        return ERR_PTRNULL;
    }

    consumer->workers = (worker_t *)calloc(size, sizeof(worker_t));
    if (!consumer->workers)
    {
        return ERR_MEMORY;
    }

    consumer->size = size;
    consumer->state = STATE_INIT;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e consumer_run(consumer_t *consumer)
{
    printf("%s(): invoke\n", __func__);

    if (!consumer)
    {
        return ERR_PTRNULL;
    }
    if (consumer->state != STATE_INIT)
    {
        return ERR_INTERNAL;
    }

    for (size_t i = 0; i < consumer->size; ++i)
    {
        consumer->workers[i].state = STATE_IDLE;
        if (pthread_mutex_init(&(consumer->workers[i].mutex), NULL) != 0)
        {
            return ERR_INTERNAL;
        }
        if (pthread_create(&(consumer->workers[i].pthread), NULL, &worker_loop, &(consumer->workers[i])) != 0)
        {
            return ERR_INTERNAL;
        }
    }

    consumer->state = STATE_RUN;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e consumer_stop(consumer_t *consumer)
{
    printf("%s(): invoke\n", __func__);

    if (!consumer)
    {
        return ERR_PTRNULL;
    }
    if (consumer->state != STATE_RUN)
    {
        return ERR_INTERNAL;
    }

    consumer->state = STATE_STOP;
    for (size_t i = 0; i < consumer->size; ++i)
    {
        consumer->workers[i].state = STATE_STOP;
        pthread_join(consumer->workers[i].pthread, NULL); // TODO: error check
    }

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

err_code_e consumer_add_worker_task(consumer_t *consumer, size_t worker, task_t *task)
{
    printf("%s(): invoke\n", __func__);

    if (!consumer)
    {
        return ERR_PTRNULL;
    }
    if (!task)
    {
        return ERR_PTRNULL;
    }
    if (consumer->size < worker)
    {
        return ERR_INTERNAL;
    }

    worker_t *w = &(consumer->workers[worker]);

    pthread_mutex_lock(&(w->mutex));
    w->task = task;
    printf("%s(): task = %d\n", __func__, w->task->data);
    pthread_mutex_unlock(&(w->mutex));
    w->state = STATE_RUN;

    printf("%s(): done\n", __func__);
    return ERR_NONE;
}

state_e consumer_get_worker_state(consumer_t *consumer, size_t worker)
{
    if (!consumer)
    {
        return ERR_PTRNULL;
    }
    if (consumer->size < worker)
    {
        return ERR_INTERNAL;
    }

    return consumer->workers[worker].state;
}

err_code_e consumer_print_statistic(consumer_t *consumer)
{
    if (!consumer)
    {
        return ERR_PTRNULL;
    }

    for (size_t i = 0; i < consumer->size; ++i)
    {
        char buf[256] = { 0 };
        size_t n = snprintf(buf, 256,  "worker %ld done %d tasks\n", i, consumer->workers[i].statistic);
        write(1, buf, n);
    }

    return ERR_NONE;
}