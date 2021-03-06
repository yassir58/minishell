#include "../includes/minishell.h"

int     check_space(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isspace(str[i]))
            return (1);
        i++;
    }
    return (0);
}

char    *prompt(char *string)
{
    char *line;

    line = readline(string);
    if (line)
    {
        if (ft_strlen(line) > 0)
        {
            if (check_space(line))
                add_history(line);
            else
                line = prompt(string);
        }
        else
            line = prompt(string);
    }
    else
        exit(EXIT_FAILURE);
    return (line);
}