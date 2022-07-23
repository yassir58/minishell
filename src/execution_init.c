#include "../includes/minishell.h"


    /// check for valid commands
    /// handle redirections
    /// execute commands
    /// exit
    /// wait for exit status of child

void init_command (shell_args_t *args)
{
    // if (args->exec_node->next == NULL)
    //     handle_simple_command (args);
    // else
    //     test_piped_commands (args);
}


int get_status (int pid)
{
    int status;

    waitpid (pid, &status, 0);
    if (WIFEXITED(status))
         printf ("exit status %d\n", WEXITSTATUS(status));
    return (status);
}
 
