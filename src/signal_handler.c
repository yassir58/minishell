#include "../includes/minishell.h"

void	handler(int signum)
{
    if (signum == SIGINT && (g_data->heredoc_status == 0 && !g_data->fork_status))
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("",0);
        rl_redisplay();
    }
    else if (signum == SIGINT && g_data->heredoc_status != 0)
    {
        kill(g_data->heredoc_status, SIGKILL);
        g_data->heredoc_status = 0;
    }
    else if (signum == SIGINT && g_data->fork_status != 0)
    {
        kill (g_data->fork_status, SIGKILL);
        g_data->fork_status = 0;
    }
}

void    init_signals(void)
{
    signal(SIGINT, handler);
    signal(SIGSTOP, SIG_IGN);
}
