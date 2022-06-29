#include "../includes/minishell.h"

int     check_space(char *str)
{
    int i;

    i = 0;
    while (str[i] && ft_isspace(str[i]))
    {
        if (!ft_isspace(str[i]))
            return (1);
        i++;
    }
    return (0);
}

char    *prompt(void)
{
    char *line;

    line = readline("@minishell>>");
    if (line)
    {
        if (ft_strlen(line) > 0)
        {
            if (!check_space(line))
                add_history(line);
            else
                line = prompt();
        }
    }
    else
        exit(1);
    return (line);
}