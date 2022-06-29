#include "../includes/minishell.h"

// int execution_function (shell_args_t *args)
// {
//     t_exec_node *tmp;
//     int id;
//     int **fds;
//     int i;
//     int len;
//     int indx;

//     i = 0;
//     indx = 0;
//     len = nodes_number(args);
//     tmp = args->exec_node;
   
//     // if (!tmp->next)
//     // {
//     //     if (tmp->builtin == true)
//     //             builtin_routine (args, tmp);
//     //     else
//     //     {
//     //         id = fork ();
//     //         if (id == 0)
//     //             exec_command (args, tmp);
//     //     }
//     // }
//     // else
//     // {
//         fds = malloc (sizeof (int *) * (len - 1));
//         fds[len - 1] = NULL;
//         while (i < (len - 1))
//         {
//             fds[i] = malloc (sizeof (int)  * 2);
//             if (pipe (fds[i]) == -1)
//                 printf ("pipe failed \n");
//             i++;
//         }
//     //     while (tmp)
//     //     {
//     //         if (tmp->builtin == true)
//     //             builtin_routine (args, tmp);
//     //         else
//     //         {
//     //             id = fork ();
//     //             if (!id)
//     //             {
//     //                 if (tmp->next)
//     //                 {
//     //                     close (fds[indx][READ_END]);
//     //                     dup2 (fds[indx][WRITE_END], STDOUT_FILENO);
//     //                     close (fds[indx][WRITE_END]);
//     //                 }
//     //                 if (tmp->prev)   
//     //                 {
//     //                     close (fds[indx - 1][WRITE_END]);
//     //                     dup2 (fds[indx - 1][READ_END], STDIN_FILENO) ;
//     //                     close (fds[indx - 1][READ_END]);
//     //                 }
//     //                 exec_command (args, tmp);
//     //                 printf ("indx:%d\n", indx);
//     //             }
//     //         }
//     //         indx++;
//     //         tmp = tmp->next;
//     //     }
//     // }
//     i = 0;
//     while (i < len)
//     {
//         if (close (fds[i][READ_END] == -1))
//             printf ("close fd failed !\n");
//         if (close (fds[i][WRITE_END]) == -1)
//             printf ("close fd failed !\n");
//         i++;
//     }
//     free_tab (fds);
//     // while (waitpid (-1, NULL, 0) != -1);
//     return (0);
// }

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