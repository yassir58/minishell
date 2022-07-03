#include "../includes/minishell.h"


int execution_chain (shell_args_t *args)
{
   t_exec_node *tmp;
   int id;
   int **fds;
   int indx;
   int err;

   indx = 0;
   err = 0;
   tmp = args->exec_node;
   fds = open_fd_table (nodes_number(args), args);
   if (!fds)
    return (-1);
   while (tmp)
   {
        if (tmp->builtin)
           handle_builtin (args, tmp, fds, indx);
        else
        {
            id = fork_child (args);
            if (!id)
                handle_redirected_command (args, tmp, fds, indx);
        }
        indx++;
        tmp = tmp->next;
   }
    close_fd_table (fds);
    get_childer_status ();
   return (0);
}

void handle_redirected_command (shell_args_t *args, t_exec_node *tmp, int **fds, int indx)
{
      handle_redirections (args, tmp->cmd->redir_list);
      if (tmp->prev != NULL && tmp->next != NULL)
         handle_doubly_piped (indx, fds);
      else if (tmp->next == NULL && tmp->prev != NULL)
         handle_last_command (indx, fds);
      else if (tmp->next != NULL && tmp->prev == NULL)
         handle_first_command (indx, fds);
      exec_command (args, tmp);
}


int builtin_routine (shell_args_t *args, t_exec_node *exec_node)
{
    char **command;

    command = get_commands (exec_node->cmd->cmds);
    if (!ft_strcmp (command[0], "cd"))
    {
        /*  optional functionality */
        if (number_of_el (command) > 2)
            cd_function (NULL, -1, &args->env_list);
        /**/
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
    char **command;
    char *path;
    char **path_check;
    char *cmd;

    command = get_commands (exec_node->cmd->cmds);
    path_check = check_for_path (command[0]);
    if (path_check)
    {
        path = path_check[0];
        cmd  = path_check [1];
        command[0] = cmd;
        path = check_access (command[0], path);
        free_tab (path_check);
    }
    else
    {
         path = check_access (command[0], NULL);
         cmd  = command[0];
    }
    if (path == NULL)
        printf ("%s: command not found\n", cmd);
    else
        execve (path, command, args->env);  
}


char **check_for_path (char *cmd)
{
    char **path_table;
    char **cmd_path;
    char *dir_name;
    int i;

    path_table = NULL;
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