#include "../includes/minishell.h"

void pwd_function (env_list_t *env_list)
{
    char *pwd;
    
    pwd = get_pwd (env_list);
    printf ("%s\n", pwd);
}

int cd_function (char *arg, int flag, env_list_t **env_list)
{
    int i;
    int err;

    i = 0;
    err = 0;
    if (flag == -1)
        write (2 ,"cd: Arguments Err \n", 19);
    else
    {
        if (arg == NULL)
            cd_to_home (*env_list);
        else if (!strcmp (arg, "~"))
            cd_to_home (*env_list);
        else
        {
            err = chdir (arg);
            if (err == -1)
            {
                err  = check_for_dots (arg, *env_list);
                if (err == -1)
                    printf ("no such file or directory : %s\n", arg);
            }
        }
        update_pwd_env (env_list);
    }
    return (0);
}

void echo_function (char *argv[], int argc)
{
    int i = 1;
    char thrilling;

    thrilling = '\n';
    if (argc > 1)
    {
        if (!strcmp (argv[i], "-n"))
        {
            thrilling = '\0';
            while (argv[i] && !strcmp (argv[i], "-n"))
                i++;
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
}