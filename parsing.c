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
                increment_counters (&len, &i);
            if (len)
                increment_counters (&count, &i);
        }
        else
        {
            while (line[i] && line[i] != ' ' && line[i] != '"' && line[i] !='\'')
                increment_counters (&len, &i);
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
    int len;

    len = 0;
    arg = NULL;
    i = *ptr;
    while (line[i] && line[i] == ' ')
            i++;
    if (line[i] == '"' || line[i]  == '\'')
    {
        if (line[i] == line[i + 1])
        {
            i += 2;
            arg = malloc (sizeof(char));
            arg[0] = 0;
        }
        else
            arg = handle_quote (line , &i);
    }
    else
    {
        while (line[i] && line[i] != ' ' && line[i] != '"' && line[i] != '\'')
            increment_counters (&len, &i);
        if (len)
        {
            arg = malloc (sizeof (char)* (len + 1));
            ft_strlcpy (arg, &(line[i - len]), (len + 1));
        }
    }
    *ptr = i;
    return (arg);
}


char **get_command(int *acount)
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
    *acount = count;
    if (!count)
        return (NULL);
    args = malloc (sizeof (char*) * (count + 1));
    if (!args)
        return (NULL);
    while (input != NULL)
    {
        input = get_input (line , &indx);
        printf ("%s\n", input);
        args[i] = input;
        i++;
    }
    free (line);
    return (args);
}

void increment_counters (int *len , int *i)
{
    (*i)++;
    (*len)++;
}