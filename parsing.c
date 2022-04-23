#include "minishell.h"


int arg_count (char *line)
{
    int count;
    int i;
    int len;
    char delim;
    int done;

    len = 0;
    done = 0;
    i = 0;
    count = 0;
    while (!done)
    {
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i] == '"' || line[i] == '\'')
        {
            delim = line[i++];
            while (line[i] && line[i] != delim)
            {
                i++;
                len++;
            }
            if (len)
            {
                i++;
                count++;
            }
        }
        else
        {
            while (line[i] && line[i] != ' ' && line[i] != '"' && line[i] !='\'')
            {
                i++;
                len++;
            }
            if (len)
                count++;
        }
        if (!line[i])
            done = 1;
    }
    
    return (count);
}

char *get_input (char *line, int *ptr)
{
    int i;
    char *arg;
    char delim;
    int len;


    len = 0;
    arg = NULL;
    i = *ptr;
    while (line[i] && line[i] == ' ')
            i++;
    if (line[i] == '"' || line[i]  == '\'')
    {
        delim = line[i++];
        while (line[i] && line[i] != delim)
        {
            len++;
            i++;
        }
        if (len)
        {
            arg = malloc (sizeof (char)* (len + 1));
            ft_strlcpy (arg, &(line[i++ - len]), (len + 1));
        }
    }
    else
    {
        while (line[i] && line[i] != ' ' && line[i] != '"' && line[i] != '\'')
        {
            len++;
            i++;
        }
        if (len)
        {
            arg = malloc (sizeof (char)* (len + 1));
            ft_strlcpy (arg, &(line[i - len]), (len + 1));
        }
    }
    *ptr = i;
    return (arg);
}


char **get_command()
{
    char *line;
    char *input;
    char **args;
    int count;
    int i;
    int indx;

    i = 0;
    indx = 0;
    line = readline (">");
    input = "";
    count = arg_count (line);
    args = malloc (sizeof (char*) * (count + 1));
    if (!count || !args)
        return (NULL);
    while (input != NULL)
    {
        input = get_input (line , &indx);
        printf ("input : %s\n", input);
        args[i] = input;
        i++;
    }
    return (args);
}
