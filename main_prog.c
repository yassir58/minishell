#include "minishell.h"


int init_command (char **args, int count)
{
    char *status;
    int flag;
    int err;

    /// validate args
    /// executs command
    err = input_validation (args, count);

    // if (err)
    // {
    //     execute ();
    // }

    free_tab (args);
    status = args[0];
    flag = strcmp (status, "exit");
    return (flag);
}




int main ()
{
    char **args;
    int flag;
    int count;


    flag = 1;
    while (flag)
    {
        args = get_command (&count);
        if (args)
            init_command (args, count);
    }
    //exec_command ();
    return (0);
}