#include "../includes/minishell.h"

int is_number(char *str)
{
    // This function should be redone.
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
    {
        if (ft_strlen(str) == 1)
            return (0);
        i++;
    }
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}