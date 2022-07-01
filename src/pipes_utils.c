#include "../includes/minishell.h"


void handle_pipeline (shell_args_t *args)
{
    t_exec_node *tmp;
    int id;
    int **fds;
    int indx;
    int err;

    indx = 0;
    err = 0;
    tmp = args->exec_node;

      fds =  open_fd_table (nodes_number(args), args);
      while (tmp)
      {
         if (tmp->builtin)
               builtin_routine (args, tmp);
         else
         {
            id = fork_child (args);
            if (!id)
            {
               if (tmp->cmd->cmds == NULL)
                  handle_redirections (tmp);
               else
                  handle_redirected_command (args, tmp, fds, indx);
            }
         }
         indx++;
         tmp = tmp->next;
      }
        close_fd_table (fds);
}

void handle_redirected_command (shell_args_t *args, t_exec_node *tmp, int **fds, int indx)
{
      handle_redirections (tmp);
      if (tmp->prev != NULL && tmp->next != NULL)
         handle_doubly_piped (indx, fds);
      else if (tmp->next == NULL && tmp->prev != NULL)
         handle_last_command (indx, fds);
      else if (tmp->next != NULL && tmp->prev == NULL)
         handle_first_command (indx, fds);
      exec_command (args, tmp);
}
