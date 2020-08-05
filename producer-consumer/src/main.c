#include <producer/producer.h>
#include <consumer/consumer.h>
#include <scheduler/scheduler.h>
#include <signal/signal.h>

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


static volatile int run = 1;
static volatile int show_stat = 0;

static void signal_handler(int signo, siginfo_t *info, void *extra)
{
    extra = extra;
    info = info;

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
    if (s)
    {
        printf("stop `scheduler` ...\n");
        scheduler_stop(s);
    }
    if (p)
    {
        printf("stop `producer` ...\n");
        producer_stop(p);
    }
    if (c)
    {
        printf("stop `consumer` ...\n");
        consumer_stop(c);
    }

    if (s)
    {
        printf("shutdown `scheduler` ...\n");
        scheduler_destroy(&s);
    }
    if (p)
    {
        printf("shutdown `producer` ...\n");
        producer_destroy(&p);
    }
    if (c)
    {
        printf("shutdown `consumer` ...\n");
        consumer_destroy(&c);
    }
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

    const int workers = atoi(argv[1]);

    signal_init(SIGUSR1, signal_handler);
    signal_init(SIGINT,  signal_handler);
    signal_init(SIGTERM, signal_handler);

    producer_t *producer = producer_create();
    if (!producer)
    {
        fprintf(stderr, "can't allocate memory for producer");
        return ERR_MEMORY;
    }

    consumer_t *consumer = consumer_create();
    if (!consumer)
    {
        fprintf(stderr, "can't allocate memory for consumer");
        cleanup(producer, NULL, NULL);
        return ERR_MEMORY;
    }

    scheduler_t *scheduler = scheduler_create();
    if (!scheduler)
    {
        fprintf(stderr, "can't allocate memory for scheduler");
        cleanup(producer, consumer, NULL);
        return ERR_MEMORY;
    }

    if (consumer_init(consumer, workers) != ERR_NONE)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_INTERNAL;
    }
    if (scheduler_init(scheduler, consumer) != ERR_NONE)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_INTERNAL;
    }
    if (producer_init(producer, scheduler) != ERR_NONE)
    {
        cleanup(producer, consumer, scheduler);
        return ERR_INTERNAL;
    }

    if (consumer_run(consumer)  != ERR_NONE)
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

    printf("> %d pid\n", getpid());

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
