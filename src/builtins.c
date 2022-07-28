#include "../includes/minishell.h"

int pwd_function (env_list_t *env_list)
{
    char *pwd;
    
    pwd = get_pwd (env_list);
    printf ("%s\n", pwd);
    return (0);
}

int cd_function (char *arg, int flag, env_list_t **env_list)
{
    int i;
    int err;

    i = 0;
    err = 0;
    if (flag == -1)
        builtin_err ("cd: Arguments Err \n", NULL);
    else
    {
        if (arg == NULL)
            cd_to_home (*env_list);
        else if (!strcmp (arg, "~"))
            cd_to_home (*env_list);
        else if (!strcmp (arg, "-"))
             cd_prev_pwd (*env_list);
        else
        {
            err = chdir (arg);
            if (err == -1)
                    builtin_err (" :no such file or directory\n", arg);
        }
        update_pwd_env (env_list);
    }
    return (0);
}

int echo_function (char *argv[], int argc)
{
    int i = 1;
    char thrilling;

    thrilling = '\n';
    if (argc > 1)
    {
        if (check_for_valid_option (argv[i]) == 1)
        {
            while (argv[i] && (check_for_valid_option (argv[i]) == 1))
                i++;
            thrilling = '\0';
        }
        while (argv[i])
        {
            if (i == (argc - 1))
                printf ("%s", argv[i]);
            else
                printf ("%s ", argv[i]);
            i++;
        }
    }
    if (thrilling)
        printf ("%c", thrilling);
    return (0);
}


int builtin_err (char *err, char *arg)
{
    char *res;
    if (arg)
        res = ft_strjoin (arg, err);
    else
        res = err;
    ft_putstr_fd (res, 2);
    return (1);
}