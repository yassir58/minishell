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
      //handle_redirections (args, tmp->cmd->redir_list);
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
    free_tab (command);
    return (0);
}

void exec_command (shell_args_t *args, t_exec_node *exec_node)
{
    char **command;
    char *path;

    command = get_commands (exec_node->cmd->cmds);
    path = check_access (command[0]);
    if (path == NULL)
        printf ("%s: command not found\n", command[0]);
    else
        execve (path, command, NULL);  
}