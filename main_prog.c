#include "minishell.h"

int main ()
{
    char *command;
    char **args;
    int flag;
    int count;


    flag = 1;
    command = "";
    while (flag)
    {
        args = get_command (&count);
        //input_validation (args, count);
        command = args[0];
        flag = strcmp (command, "exit");
        free_tab (args);
    }
    return (0);
}