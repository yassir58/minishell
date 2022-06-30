#include "../includes/minishell.h"



void close_fd_table (int **fd_table)
{
    int i;

    i = 0;
    while (fd_table[i])
    {
        close_fd (fd_table[i][READ_END]);
        close_fd (fd_table[i][WRITE_END]);
        free (fd_table[i]);
        i++;
    }
    free (fd_table);
}


int **open_fd_table (int size , shell_args_t *args)
{
    int **fd_table;
    int i;

    i = 0;
    fd_table = malloc (sizeof (int *) * size);
    if (!fd_table)
        return (allocation_err ());
    fd_table[size - 1] = NULL;
    while (i < (size - 1))
    {
        fd_table[i] = malloc (sizeof (int)  * 2);
        open_pipe (fd_table[i], args);
        i++;
    }
    return (fd_table);
}


void close_unused_fds (int **fds_table , int used)
{
    int i;

    i = 0;
    while (fds_table[i])
    {   
        if (i != used)
        {
            close_fd (fds_table[i][READ_END]);
            close_fd (fds_table[i][WRITE_END]);
        }
        i++;
    }
}
void close_unused_fds_2 (int **fds_table , int used1, int used2)
{
    int i;

    i = 0;
    while (fds_table[i])
    {   
        if (i != used1 && i != used2)
        {
            close_fd (fds_table[i][READ_END]);
            close_fd (fds_table[i][WRITE_END]);
        }
        i++;
    }
}
