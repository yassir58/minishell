#include "../includes/minishell.h"

void	handler(int signum, siginfo_t *info, void *p)
{

}


void    handle_signals(void)
{
    struct sigaction sa;

    sa.__sigaction_u.__sa_sigaction = &handler;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_mask = NULL; // I should use this field to add the set of signals that needs to be blocked.
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa, SIGTERM);
    sigaction(SIGINT, &sa, );
}