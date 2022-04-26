#include "minishell.h"


char *handle_quote (char *line, int *indx)
{
    int len;
    int i;
    char delim;
    char *arg;

    len =  0;
    i = *indx;
    arg = NULL;
    delim = line[i++];
    printf ("starting indx %d\n", i);
    while (line[i] && line[i] != delim)
    {
        len++;
        i++;
    }
    if (len && line[i] == delim)
    {
        arg = malloc (sizeof (char)* (len + 1));
        ft_strlcpy (arg, &(line[i++ - len]), (len + 1));
    }
    else
    {
        printf ("Unclosed quote Error \n");
        exit (1);
    }
    printf ("ending indx %d\n", i);
    *indx = i;
    return (arg);
}



int input_validation (char **args, int count)
{
    int i;

    i = 0;
    while (i < count - 1)
    {
        if (!args[i])
        {
            printf ("quote Error \n");
            return (0);
        }
        i++;
    }
    return (1);
}