#include <signal/signal.h>

#include <signal.h>
#include <stddef.h>


err_code_e signal_init(int sig, void *handler)
{
    struct sigaction action = { 0 };
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;
 
    if (sigaction(sig, &action, NULL) == -1) { 
        return ERR_INTERNAL;
    }
    return ERR_NONE;
}

err_code_e signal_block()
{
    sigset_t mask = { 0 };
    sigfillset(&mask);
    pthread_sigmask(SIG_BLOCK, &mask, NULL);
    return ERR_NONE;
}
