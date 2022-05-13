#include "minishell.h"


char *handle_quote (char *line, int *indx)
{
    int len;
    int i;
    char delim;
    char *arg;
    // int count;

    len =  0;
    // count = 0;
    i = *indx;
    arg = NULL;
    delim = line[i++];
    while (line[i] && line[i] != delim)
        increment_counters (&len, &i);
    if (len && line[i] == delim)
    {
        arg = malloc (sizeof (char)* (len + 1));
        ft_strlcpy (arg, &(line[i++ - len]), (len + 1));
    }
    else
        printf ("Unclosed quote Error \n");
    *indx = i;
    return (arg);
}

int input_validation (char **args, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        if (!args[i])
            return (0);
        i++;
    }
    return (1);
}


int get_quote_count (char delim, char *str, int indx)
{
    int count;

    count = 0;
    while (str[indx] && str[indx] == delim)
    {
        indx++;
        count++;
    }
    return (count);
}