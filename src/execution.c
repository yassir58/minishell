#include "../includes/minishell.h"

void test_piped_commands (shell_args_t *args)
{
    t_exec_node *tmp;
    int **fds;
    int indx;
    int id;

    indx = 0;
    tmp = args->exec_node;
    fds = open_fd_table (nodes_number(args), args);
    while (tmp)
    {
        id = fork_child (args);
        if (!id)
        {
            if (tmp->builtin)
                handle_builtin (args, tmp, fds, indx);
            else
            {
                link_pipes (tmp, fds, indx);
                exec_command (args, tmp);
            }
        }
        indx++;
        tmp = tmp->next;
    }
    close_fd_table (fds);
}

void link_pipes (t_exec_node *tmp, int **fds, int indx)
{
    if (tmp->prev != NULL && tmp->next != NULL)
        handle_doubly_piped (indx, fds);
    else if (tmp->next == NULL && tmp->prev != NULL)
        handle_last_command (indx, fds);
    else if (tmp->next != NULL && tmp->prev == NULL)
        handle_first_command (indx, fds);
}


int builtin_routine (shell_args_t *args, t_exec_node *exec_node)
{
    char **command;

    command = get_commands (exec_node->cmd->cmds);
    if (!ft_strcmp (command[0], "cd"))
    {
        if (number_of_el (command) > 2)
            cd_function (NULL, -1, &args->env_list);
        else if (number_of_el (command) == 2)
            cd_function (command[1], 1, &args->env_list);
        else 
            cd_function (NULL, 1, &args->env_list);
    }
    else if (!advanced_strcmp (command[0], "pwd"))
        pwd_function (args->env_list);
    else if (!advanced_strcmp (command[0], "echo"))
        echo_function (command, number_of_el (command));
    else if (!advanced_strcmp (command[0], "env"))
        ft_env (exec_node, args->env_list, args);
    else if (!advanced_strcmp (command[0], "unset"))
        ft_unset (exec_node, args->env_list, args);
    else if (!advanced_strcmp (command[0], "exit"))
        ft_exit (exec_node, args->env_list, args);
    free_tab (command);
    return (0);
}

void exec_command (shell_args_t *args, t_exec_node *exec_node)
{
    char **cmds;
    char **path;


    cmds = get_commands (exec_node->cmd->cmds);
    path = get_path (args, cmds);    
    if (!path[0])
        shell_err (cmds[0]);
    execve (path[0], cmds, args->env);
}



char **check_for_path (char *cmd)
{
    char **path_table;
    char **cmd_path;
    char *dir_name;
    int i;

    path_table = NULL;
    cmd_path = NULL;
    i = 0;
    if (ft_strchr (cmd, '/'))
    {
        path_table = ft_split (cmd, '/');
        if (cmd[0] == '/' )
            cmd_path = handle_absolue_path (path_table);
        else
            cmd_path = handle_relative_path (path_table);
        free_tab (path_table);
    }
    return (cmd_path); 
}


char **handle_absolue_path (char **path_table)
{
    char **cmd_path;
    char *dir_name;
    int i;

    i = 0;
    dir_name = NULL;
    cmd_path = malloc (sizeof (char*) * 3);
    if (!cmd_path)
        allocation_err ();
    cmd_path[2] = NULL;
    cmd_path[0] = ft_strdup ("");
    while (path_table[i])
    {
        if (!path_table[i + 1])
            break;
        dir_name = ft_strjoin ("/", path_table[i]);
        cmd_path[0] = ft_strjoin (cmd_path[0], dir_name);
        i++;
    }
    cmd_path[1] = ft_strdup (path_table[i]);
    return (cmd_path);
}

char **handle_relative_path (char **path_table)
{
    char **cmd_path;
    char *dir_name;
    int i;

    i = 0;
    dir_name = NULL;
    cmd_path = malloc (sizeof (char*) * 3);
    if (!cmd_path)
        allocation_err ();
    cmd_path[2] = NULL;
    cmd_path[0] = ft_strdup ("");
    while (path_table[i])
    {
        if (!path_table[i + 1])
            break;
        if (!i)
            dir_name = path_table[i];
        else
            dir_name = ft_strjoin ("/", path_table[i]);
        cmd_path[0] = ft_strjoin (cmd_path[0], dir_name);
        i++;
    }
    cmd_path[1] = ft_strdup (path_table[i]);
    return (cmd_path);
}

int handle_simple_command (shell_args_t *args)
{
    int id;

    id = fork_child (args);
    if (id == 0)
    {
        if (args->exec_node->builtin)
            builtin_routine (args, args->exec_node);
        else
            exec_command (args, args->exec_node);
    }
    return (id);
}


void shell_err (char *command)
{
    ft_putstr_fd (ft_strjoin (command, ": command not found\n"), STDERR_FILENO);
    exit (127);
}

char **get_path (shell_args_t *args, char **cmds)
{
    char *path;
    char **path_check;
    char **path_table;
    char *cmd;

    path_table = malloc (sizeof (char *) * 3);
    path_check = check_for_path (cmds[0]);
    path = NULL;
    path_table[2] = NULL;
    cmd = cmds[0];
    if (path_check)
    {
        path = path_check[0];
        path_table[1] = path_check[1];
        cmd = path_table[1];
    }
    else
        path_table[1] = cmds[0];
    path = check_access (path_table[1], path);
    printf ("hello p %s \n", path);
    printf ("hello s %s \n", path);
    path_table[0] = path;
    return (path_table);
}