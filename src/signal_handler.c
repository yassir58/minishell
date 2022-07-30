#include "../includes/minishell.h"

void	handler(int signum)
{
    if (signum == SIGINT && heredoc_status == 0)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("",0);
        rl_redisplay();
    }
    else if (signum == SIGINT && heredoc_status != 0)
    {
        kill(heredoc_status, SIGKILL);
        heredoc_status = 0;
    }
}

void    init_signals(void)
{
    signal(SIGINT, handler);
    signal(SIGSTOP, SIG_IGN);
}
