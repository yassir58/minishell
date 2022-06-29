#include "../includes/minishell.h"

int execution_function (shell_args_t *args)
{
    t_exec_node *tmp;
    int id;
    int **fds;
    int indx;

    indx = 0;
    tmp = args->exec_node;
   
    if (!tmp->next)
    {
        /// hadnle riderictions
        if (tmp->builtin == true)
                builtin_routine (args, tmp);
        else
        {
            id = fork ();
            if (id == 0)
                exec_command (args, tmp);
        }
    }
    else
    {
        fds =  open_fd_table (nodes_number(args), args);
        while (tmp)
        {
            if (tmp->builtin)
                builtin_routine (args, tmp);
            else
            {
                id = fork_child (args);
                if (id == 0)
                {
                    if (tmp->prev != NULL && tmp->next != NULL)
                    {
                        close_fd (fds[0][WRITE_END]);
                        close_fd (fds[1][READ_END]);
                        dup2 (fds[0][READ_END], STDIN_FILENO);
                        dup2 (fds[1][WRITE_END], STDOUT_FILENO);
                        close_fd (fds[0][READ_END]);
                        close_fd (fds[1][WRITE_END]);
                    }
                    else if (tmp->next == NULL && tmp->prev != NULL)
                    {
                        close_fd (fds[1][WRITE_END]);
                        close_fd (fds[0][READ_END]);
                        close_fd (fds[0][WRITE_END]);
                        dup2 (fds[1][READ_END], STDIN_FILENO);
                        close_fd (fds[1][READ_END]);
                    }
                    else if (tmp->next != NULL && tmp->prev == NULL)
                    {
                        close_fd (fds[0][READ_END]);
                        close_fd (fds[1][WRITE_END]);
                        close_fd (fds[1][READ_END]);
                        dup2 (fds[0][WRITE_END], STDOUT_FILENO);
                        close_fd (fds[0][WRITE_END]);
                    }
                    exec_command (args, tmp);
                }
            }
            indx++;
            tmp = tmp->next;
        }
        close_fd_table (fds);
    }
    while (waitpid (-1, NULL, 0) != -1);
    return (0);
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

void handle_builtin (shell_args_t *args, t_exec_node *exec_node)
{
    builtin_routine (args, exec_node);   
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