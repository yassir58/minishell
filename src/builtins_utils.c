#include "../includes/minishell.h"

int cd_prev_pwd (env_list_t *env_list)
{
    env_list_t *tmp;
    int err;

    tmp = env_list;
    while (tmp)
    {
        if (!(strcmp (tmp->variable_name, "OLDPWD")))
            break ;
        tmp = tmp->next;
    }
    err = chdir (tmp->value);
    if (err == -1)
            return (builtin_err (" :no such file or directory\n", tmp->value));
    return (0);
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

char *get_pwd_env (env_list_t *list)
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


int update_pwd_env (env_list_t **list)
{
    char *current;
    char *old;
    env_list_t *tmp;

    tmp = *list;
    current = getcwd (NULL, 0);
    if (!current)
        return (-1);
    old = get_pwd_env (*list);
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

char *get_pwd (env_list_t *env_list)
{
    char *buffer;

    buffer = NULL;
    buffer = getcwd (NULL, 0);
    if (!buffer)
        buffer = get_pwd_env (env_list);
    return (buffer);
}

int check_for_valid_option (char *option)
{
    int i;

    i = 0;
    if (option[i] == '-')
    {
        i++;
        while (option [i] && option[i] == 'n')
            i++;
        if (option[i] == 0)
            return (1);
    }
    return (0);
}