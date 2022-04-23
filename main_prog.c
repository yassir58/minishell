#include "minishell.h"

int main ()
{
    char *command;
    char **args;
    int flag;


    flag = 1;
    command = "";
    while (flag)
    {
        args = get_command ();
        command = args[0];
        flag = strcmp (command, "exit");
        free_tab (args);
    }
    return (0);
}