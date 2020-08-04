#include <producer/producer.h>
#include <consumer/consumer.h>
#include <scheduler/scheduler.h>
#include <signal/signal.h>

#include <stdio.h>
#include <signal.h>

int run = 1;
consumer_t *consumer = NULL;

static void signal_usr_handler(int signo, siginfo_t *info, void *extra) 
{
    consumer_print_statistic(consumer);
}

static void signal_term_handler(int signo, siginfo_t *info, void *extra) 
{
    run = 0;
}

int main(int argc, char const *argv[])
{
    // TODO: check cmd-line arguments
    signal_init(SIGUSR1, signal_usr_handler);
    signal_init(SIGINT,  signal_term_handler);
    signal_init(SIGTERM, signal_term_handler);

    producer_t *producer = producer_create();
    if (!producer)
    {
        fprintf(stderr, "can't allocate memory for producer");
        return ERR_MEMORY;
    }

    consumer = consumer_create();
    if (!consumer)
    {
        fprintf(stderr, "can't allocate memory for consumer");
        producer_destroy(&producer);
        return ERR_MEMORY;
    }

    scheduler_t *scheduler = scheduler_create();
    if (!scheduler)
    {
        fprintf(stderr, "can't allocate memory for scheduler");
        consumer_destroy(&consumer);
        producer_destroy(&producer);
        return ERR_MEMORY;
    }

    consumer_init(consumer, 5);
    scheduler_init(scheduler, consumer);
    producer_init(producer, scheduler);

    consumer_run(consumer);
    scheduler_run(scheduler);
    producer_run(producer);

    printf("> %d pid\n", getpid());

    while (run == 1) {
        sleep(1);
    }

    producer_stop(producer);
    scheduler_stop(scheduler);
    consumer_stop(consumer);

    scheduler_destroy(&scheduler);
    consumer_destroy(&consumer);
    producer_destroy(&producer);
    return ERR_NONE;
}
