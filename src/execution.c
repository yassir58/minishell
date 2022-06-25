#include "../includes/minishell.h"


int builtin_routine (shell_args_t *args)
{
    char *cmd;
    char *arg;

    cmd = args->exec_node->cmd->cmds->cmd;
    arg = args->exec_node->cmd->cmds->next->cmd;
    if (!ft_strcmp (cmd, "cd"))
    {
        printf ("cmd:%s args:%s\n", cmd, arg);
        cd_function (arg, 1, &args->env_list);
    }
    return (0);
}