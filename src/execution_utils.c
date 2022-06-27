#include "../includes/minishell.h"

void link_pipes (shell_args_t *args)
{
    t_exec_node *tmp;
    int fds[2];
    int err;

    tmp = args->exec_node;
    err = 0;
    while (tmp)
    {
        if (tmp->prev && tmp->piped)
        {
            err = pipe (fds);
            if (err == -1)
                printf ("pipes err \n");
            tmp->prev->write_end = fds[0];
            tmp->read_end = fds[1];
        }
        tmp = tmp->next;
    }
}

void handle_piped_command (shell_args_t *args)
{
    t_exec_node *tmp;

    tmp = args->exec_node;
    while (tmp)
    {
        if (!tmp->prev && tmp->next)
        {
            close (tmp->read_end);
            dup2 (1, tmp->write_end);
        }
        else if (tmp->prev && tmp->next)
        {
            dup2 (0, tmp->read_end);
            dup2 (1, tmp->write_end);
        }
        else 
        {
            close (tmp->write_end);
            dup2 (0, tmp->read_end);
        }
    }
}

void init_fds (shell_args_t *args)
{
    t_exec_node *tmp;

    tmp = args->exec_node;
    while (tmp)
    {
        tmp->write_end = -1;
        tmp->read_end = -1;
        tmp =tmp->next;
    }
}