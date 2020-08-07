#include <signal/signal.h>
#include <producer/producer.h>
#include <consumer/consumer.h>
#include <scheduler/scheduler.h>

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


static volatile int run = 1;
static volatile int show_stat = 0;

static void signal_handler(int signo, siginfo_t *info, void *extra)
{
    extra = extra; // happy compiler
    info  = info;  // happy compiler

    if (signo == SIGUSR1)
    {
        write(2, "got `SIGUSR1` signal\n", 22);
        show_stat = 1;
    }
    else if (signo == SIGTERM)
    {
        write(2, "got `SIGTERM` signal\n", 22);
        run = 0;
    }
    else if (signo == SIGINT)
    {
        write(2, "got `SIGINT` signal\n", 21);
        run = 0;
    }
}

static void cleanup(producer_t *p, consumer_t *c, scheduler_t *s)
{
    if (s) scheduler_stop(s);
    if (p) producer_stop(p);
    if (c) consumer_stop(c);

    if (s) scheduler_destroy(&s);
    if (p) producer_destroy(&p);
    if (c) consumer_destroy(&c);
}

static void usage(const char *arg)
{
    fprintf(stderr, "usage: %s [WORKERS NUMBER]\n", arg);
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        usage(argv[0]);
        return ERR_CMDLINE;
    }

    signal_init(SIGUSR1, signal_handler);
    signal_init(SIGINT,  signal_handler);
    signal_init(SIGTERM, signal_handler);

    const int workers = atoi(argv[1]);

    producer_t  *producer  = NULL;
    consumer_t  *consumer  = NULL;
    scheduler_t *scheduler = NULL;

    consumer = consumer_create(workers);
    if (!consumer)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_MEMORY;
    }
    scheduler = scheduler_create(consumer);
    if (!scheduler)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_MEMORY;
    }
    producer = producer_create(scheduler);
    if (!producer)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_MEMORY;
    }

    if (consumer_run(consumer) != ERR_NONE)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_INTERNAL;
    }
    if (scheduler_run(scheduler) != ERR_NONE)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_INTERNAL;
    }
    if (producer_run(producer) != ERR_NONE)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_INTERNAL;
    }

    printf("\n*************************\n");
    printf("* %d pid\n", getpid());
    printf("*************************\n");

    while (run == 1)
    {
        if (show_stat)
        {
            consumer_print_statistic(consumer);
            show_stat = 0;
        }
        sleep(1);
    }

    cleanup(producer, consumer, scheduler);
    return ERR_NONE;
}
