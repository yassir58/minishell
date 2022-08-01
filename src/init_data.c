#include "../includes/minishell.h"


t_exec_utils *init_exec_utils (void)
{
    t_exec_utils *exec_utils;

    exec_utils = malloc (sizeof (t_exec_utils));
    if (!exec_utils)
        allocation_err ();
    exec_utils->fds = NULL;
    exec_utils->id = 0;
    exec_utils->infile = 0;
    exec_utils->outfile = 1;
    exec_utils->indx = 0;
    return (exec_utils);
}

g_shell_data *init_global (void)
{
    g_shell_data *g_data;

    g_data  = malloc (sizeof (g_shell_data));
    if (!g_data)
        allocation_err ();
    g_data->fork_status = 0;
    g_data->heredoc_status = 0;
    g_data->exit_code = 0;
    return (g_data);
}

shell_args_t *init_args (char *env[])
{
    shell_args_t *args;

    args = malloc (sizeof (shell_args_t));
    if (!args)
        allocation_err ();
    args->status = 0;
    args->line = NULL;
    args->prompt = NULL;
    args->env = env;
    args->env_list = get_env_list (args->env);
    args->lexer_list = NULL;
    args->exec_node = NULL;
    return (args);
}