#include "../includes/minishell.h"

int execution_function (shell_args_t *args)
{
    t_exec_node *tmp;
    int id;
    int **fds;
    int indx;
    int err;

    indx = 0;
    err = 0;
    tmp = args->exec_node;
    printf ("im in \n");
    if (!tmp->next)
    {
        if (tmp->cmd->cmds  != NULL)
        {
            if (tmp->builtin == true)
                builtin_routine (args, tmp);
            else
            {
                err = 1;
                id = fork ();
                if (id == 0)
                    exec_command (args, tmp);
            }
        }
        else
            printf ("command is NULL \n");
    }
    else
    {
        printf ("hy this is weired \n");
        print_exec_node (tmp);
    }
    if (err == 1)
    {
        while (waitpid (-1, NULL, 0) != -1)
            printf ("hell \n");
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