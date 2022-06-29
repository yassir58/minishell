#include "../includes/minishell.h"

// void handle_first_command (shell_args_t *args, t_exec_node *exec_node)
// {
    
// }

// void handle_last_command (shell_args_t *args, t_exec_node *exec_node)
// {
//     char **command;
//     char *path;

//     command = get_commands (exec_node->cmd->cmds);
//     path = check_access (command[0]);
//     execve (path, command, NULL);  
// }

// void handle_doubly_piped (shell_args_t *args, t_exec_node *exec_node)
// {
//     char **command;
//     char *path;

//     command = get_commands (exec_node->cmd->cmds);
//     path = check_access (command[0]);
//     execve (path, command, NULL);
// }

// void handle_simple_command (shell_args_t *args, t_exec_node *exec_node)
// {
//     char **command;
//     char *path;

//     command = get_commands (exec_node->cmd->cmds);
//     path = check_access (command[0]);
//     execve (path, command, NULL);
// }
// /*
// int **get_fd_table(shell_args_t *args)
// {
//     int **fd_table;
//     int size;
//     int i;
//     int err;

//     size = nodes_number (args);
//     i = 0;
//     fd_table = malloc (sizeof (int*) * (size + 1));
//     if (!fd_table)
//         return (NULL);
//     while (i < size)
//     {
//         fd_table[i] = malloc (sizeof(int) * 2);
//         err = pipe (fd_table[i]);
//         if (err == -1)
//         {
//             // free fd_table
//             return (NULL);
//         }
//         i++;
//     }
//     fd_table[size - 1] = NULL;
//     return (fd_table);
// }

int nodes_number (shell_args_t *args)
{
    t_exec_node *tmp;
    int len;

    len = 0;
    tmp = args->exec_node;
    while (tmp)
    {
        len++;
        tmp = tmp->next;
    }
    return (len);
}


// void close_fd_table (int **fd_table)
// {
//     int i;

//     i = 0;
//     while (fd_table [i])
//     {
//         close (fd_table[i][READ_END]);
//         close (fd_table[i][WRITE_END]);
//         free (fd_table[i]);
//         i++;
//     }
//     free (fd_table);
// }

// void link_pipes (shell_args_t *args)
// {
//     t_exec_node *tmp;
//     int indx;

//     indx = 0;
//     tmp = args->exec_node;
//     while (tmp)
//     {
//         tmp->pipe = args->fds_table[indx];
//         indx++;
//         tmp = tmp->next;
//     }
// }
// */
// void handle_piped_command (shell_args_t *args)
// {
//     t_exec_node *tmp;
//     int id;
//     int fds[2];
   
//     id = 0;
//     tmp = args->exec_node;
//     while (tmp)
//     {
//         if (tmp->builtin == true)
//             handle_builtin (args, tmp);
//         else
//         {
//             id = fork ();
//             if (id == 0)
//                 handle_nonbuiltin (args, tmp);
//             else 
//                 waitpid (id, NULL, 0);
//         }
//         tmp = tmp->next;
//     }
//     if (id != 0)
//         close_fd_table (args->fds_table);
// }