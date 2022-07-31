#include "../includes/minishell.h"


int init_command (shell_args_t *args)
{
    int status;

    status = 0;
    if (args->exec_node == NULL)
        return (258);
    if (args->exec_node->next == NULL)
        status = handle_simple_command (args);
    else
        status = exec_piped_commands (args);
    return (status);
}


int get_status (int pid)
{
    int status;

    waitpid (pid, &status, 0);
    if (WIFEXITED(status))
         printf ("exit status %d\n", WEXITSTATUS(status));
    return (status);
}
