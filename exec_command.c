#include "minishell.h"

int exec_command ()
{
    int id;
    char *argv[2];
    char *env[2];
    char *path = "/bin/cat";
    int err;




    argv[0] = "cat $test";
    argv[1] = NULL;
    env[0] = "test=README.md"; 
    env[1] = NULL;
    id = fork ();
    if (id == 0)
    {
        err = execve (path, argv, env);
        if (err == -1)
        {
            printf ("An error acured");
            exit (0);
        }
    }
    return (0);
}