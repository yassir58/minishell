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

t_shell_data *init_global (void)
{
    t_shell_data *g_data;

    g_data  = malloc (sizeof (t_shell_data));
    if (!g_data)
        allocation_err ();
    g_data->fork_status = 0;
    g_data->heredoc_status = 0;
    g_data->exit_code = 0;
    return (g_data);
}

t_shell_args *init_args (char *env[])
{
    t_shell_args *args;

    args = malloc (sizeof (t_shell_args));
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


void init_env_list (t_env_list **env_list)
{
    char *pwd_val;
    char *shlvl_val;
    t_env_list *temp;

    
    temp = *env_list;
    shlvl_val = ft_strdup ("SHLVL=0");
    pwd_val = ft_strjoin ("PWD=", get_pwd (*env_list));
    push_env_node (env_list, create_env_node (pwd_val, 0));
    push_env_node (env_list, create_env_node (shlvl_val, 1));
}