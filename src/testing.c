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
    if (!node)
        printf ("NULL ==> \n");
    else
    {
        print_token (node->token);
        printf ("%s \n", node->start);
        printf ("JOINABLE\n");
        //free (node);
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
