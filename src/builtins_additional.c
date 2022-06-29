#include "../includes/minishell.h"

void    ft_unset(char *str)
{
    // This function will contain the code that will unset a variable.
}

void    ft_env(char **cmds, env_list_t *list)
{
    if (number_of_el(cmds) == 1)
        print_env_list(list);
    else
        perror("illegal option\n");
}