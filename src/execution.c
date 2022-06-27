#include "../includes/minishell.h"

int execution_function (shell_args_t *args)
{
    t_exec_node *tmp;
    int id;
    int status;
    id = 0;
    tmp = args->exec_node;
    while (tmp)
    {
        if (tmp->builtin == true)
            handle_builtin (args, tmp);
        else
        {
            id = fork ();
            if (!id)
                handle_nonbuiltin (args, tmp);
            else 
            {
                waitpid (id, &status, 0);
                printf ("child %d  exited \n", id);
            }
        }
        tmp = tmp->next;
    }
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
     if (args->exec_node->piped)
        printf ("<====== piped builtin ========>");
    builtin_routine (args, exec_node);   
}

void handle_nonbuiltin (shell_args_t *args, t_exec_node *exec_node)
{
    char **command;
    char *path;

    command = get_commands (exec_node->cmd->cmds);
    path = check_access (command[0]);
    if (path != NULL)
    {
        execve (path, command, NULL);
        free_tab (command);
        exit (EXIT_SUCCESS);
    }
    else
    {
        exit (EXIT_FAILURE);
        free_tab (command);
    }
}