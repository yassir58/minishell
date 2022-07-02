#include "../includes/minishell.h"

void handle_first_command (int indx, int **fds_table)
{
    close_fd (fds_table[indx][READ_END]);
    close_unused_fds (fds_table, indx);
    dup2 (fds_table[indx][WRITE_END], STDOUT_FILENO);
    close_fd (fds_table[indx][WRITE_END]);
}

void handle_last_command (int indx, int **fds_table)
{
    close_fd (fds_table[indx - 1][WRITE_END]);
    close_unused_fds (fds_table, indx - 1);
    dup2 (fds_table[indx - 1][READ_END], STDIN_FILENO);
    close_fd (fds_table[indx - 1][READ_END]);
}

void handle_doubly_piped (int indx, int **fds_table)
{
    close_unused_fds_2 (fds_table, indx - 1, indx);
    close_fd (fds_table[indx - 1][WRITE_END]);
    close_fd (fds_table[indx][READ_END]);
    dup2 (fds_table[indx - 1][READ_END], STDIN_FILENO);
    dup2 (fds_table[indx][WRITE_END], STDOUT_FILENO);
    close_fd (fds_table[indx - 1][READ_END]);
    close_fd (fds_table[indx][WRITE_END]);
}

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

void get_childer_status (void)
{
   int flag;
   int status;

   flag = 0;
   while (flag != -1)
   {
      flag = waitpid (-1 , &status, 0);
      if (WIFEXITED(status) && flag != -1)
         printf ("%d exit status %d\n",flag, WEXITSTATUS(status));
   }
}