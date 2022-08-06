#include "../includes/minishell.h"


void init_command (t_shell_args *args)
{
    int status;

    status = 0;
    if (args->exec_node == NULL)
    {
        g_data->exit_code =(unsigned char) 258;
        return ;
    }
    if (args->exec_node->next == NULL)
        status = handle_simple_command (args);
    else
        status = exec_piped_commands (args);
    g_data->exit_code = (unsigned char) status;
}


int get_status (int pid)
{
    int status;

    waitpid (pid, &status, 0);
    if (WIFEXITED(status))
         printf ("exit status %d\n", WEXITSTATUS(status));
    return (status);
}
