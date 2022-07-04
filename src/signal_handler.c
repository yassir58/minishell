#include "../includes/minishell.h"

void	handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("",0);
        rl_redisplay();
    }
}

void    init_signals(void)
{
    signal(SIGINT, handler);
    signal(SIGSTOP, SIG_IGN);
}