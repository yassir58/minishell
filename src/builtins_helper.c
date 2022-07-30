#include "../includes/minishell.h"

int is_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}