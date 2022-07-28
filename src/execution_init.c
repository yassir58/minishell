#include "../includes/minishell.h"


    /// check for valid commands
    /// handle redirections
    /// execute commands
    /// exit
    /// wait for exit status of child

int init_command (shell_args_t *args)
{
    int status;


    if (args->exec_node == NULL)
        return (258);
    printf ("test\n");
    if (args->exec_node->next == NULL)
        status = handle_simple_command (args);
    else
        status = test_piped_commands (args);
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
 
