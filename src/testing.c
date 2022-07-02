#include "../includes/minishell.h"


void print_token (int token)
{
    if (token == OPERATOR)
        printf ("OPERATOR \n");
    else if (token == WORD)
        printf ("WORD \n");
    else if (token == SINGLE_QUOTED_SEQUENCE)
        printf ("SINGLE_QUOTED_SEQUENCE \n");
    else
        printf ("DOUBLE_QUOTED_SEQUENCE \n");
}

void testing (lexer_node_t *node)
{
    printf (" __________________ lexer output __________________\n");
    lexer_node_t *tmp;


    if (!node)
        printf ("NULL ==> \n");
    else
    {
        tmp = node;
        while (tmp)
        {
            print_token (tmp->token);
            printf ("%s \n", tmp->start);
            if (tmp->joinable)
                printf ("JOINABLE\n");
            tmp = tmp->next;
        }
    }
}

void test_env_list (env_list_t *list)
{
    env_list_t *tmp;
    env_list_t *ptr;


    tmp = list;
    while (tmp)
    {
        if (!strcmp (tmp->variable_name, "PWD") || !strcmp (tmp->variable_name, "OLDPWD"))
        {
            printf ("{name:%s}\n", tmp->variable_name);
            printf ("{value:%s}\n", tmp->value);
        }
        tmp = tmp->next;
    }
    tmp = list;
    while (tmp)
    {
        ptr = tmp;
        tmp = tmp->next;
        free (ptr);
    }
}



char *update_prompt (shell_args_t *args)
{
    char *pwd;
    char **tab;
    char *res;
    char *elm;

    elm = ":\033[0;31m$ \033[0m";
    res = NULL;
    pwd= get_pwd (args->env_list);
    if (pwd && ft_strcmp (pwd, "/"))
    {
        tab = ft_split (pwd, '/');
        res = tab[number_of_el(tab) - 1];
        res = ft_strjoin (res, elm);
        free_tab (tab);
        return (res);
    }
    else
        return (ft_strjoin(pwd, elm));
}

void print_fd_table (int **fds_table)
{
    int i;

    i = 0;
    while (fds_table[i])
    {
       
        printf ("[ %d : %d ]\n", fds_table[i][0], fds_table[i][1]);    
        i++;
    }
}