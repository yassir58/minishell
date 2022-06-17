#include "../includes/minishell.h"

int check_for_dots (char *arg, env_list_t *list)
{
    int i;
    int count;

    i = 0;
    count = 0;
    if (!ft_strncmp (arg, "..", 2))
    {
        i = 2;
        while (arg[i])
        {
            if (arg[i] != '.')
                return (-1);
            else
                count++;
            i++;
        }
        if (count > 5)
            return (-1);
        else
        {
            chdir ("..");
            while (count--)
                chdir ("..");
            return (0);
        }
    }
    return (-1);
}

void cd_to_home (env_list_t *env_list)
{
     env_list_t *tmp;

    tmp = env_list;
    while (tmp)
    {
        if (!(strcmp (tmp->variable_name, "HOME")))
            break ;
        tmp = tmp->next;
    }
    chdir (tmp->value);
}