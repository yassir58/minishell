#include "../includes/minishell.h"

int is_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return (1);
        i++;
    }
    return (0);
}