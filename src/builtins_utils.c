#include "../includes/minishell.h"

int cd_prev_pwd (t_env_list *env_list)
{
    t_env_list *tmp;
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

void cd_to_home (t_env_list *env_list)
{
    t_env_list *tmp;

    tmp = env_list;
    while (tmp)
    {
        if (!(ft_strcmp (tmp->variable_name, "HOME")))
            break ;
        tmp = tmp->next;
    }
    if (tmp) 
        chdir (tmp->value);
    else
        ft_putstr_fd ("cd :HOME not set\n", 2);
}

char *get_pwd_env (t_env_list *list)
{
    t_env_list *tmp;
    char *pwd;

    tmp = list;
    pwd = NULL;
    while (tmp)
    {
        if (!ft_strcmp (tmp->variable_name, "PWD"))
            pwd = ft_strdup (tmp->value);
        tmp = tmp->next;
    }
    return (pwd);
}


int update_pwd_env (t_env_list **list)
{
    char *current;
    char *old;
    t_env_list *tmp;

    tmp = *list;
    current = getcwd (NULL, 0);
    if (!current)
        return (-1);
    old = get_pwd_env (*list);
    while (tmp)
    {
        if (!ft_strcmp (tmp->variable_name, "PWD"))
            tmp->value = current;
        else if (!ft_strcmp (tmp->variable_name, "OLDPWD"))
            tmp->value = old;
        tmp = tmp->next;
    }
    return (0);
}

char *get_pwd (t_env_list *env_list)
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