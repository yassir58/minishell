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

char *get_pwd (env_list_t *list)
{
    env_list_t *tmp;
    char *pwd;

    tmp = list;
    pwd = NULL;
    while (tmp)
    {
        if (!strcmp (tmp->variable_name, "PWD"))
            pwd = ft_strdup (tmp->value);
        tmp = tmp->next;
    }
    return (pwd);
}


int update_pwd_env (env_list_t *list)
{
    char *current;
    char *old;
    env_list_t *tmp;

    tmp = list;
    current = getcwd (NULL, 0);
    if (!current)
        return (-1);
    old = get_pwd (list);
    while (tmp)
    {
        if (!strcmp (tmp->variable_name, "PWD"))
            tmp->value = current;
        else if (!strcmp (tmp->variable_name, "OLDPWD"))
            tmp->value = old;
        tmp = tmp->next;
    }
    return (0);
}