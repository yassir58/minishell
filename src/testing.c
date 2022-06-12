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
        if (node->joinable)
        {
            printf ("%s \n", node->start);
            printf ("JOINABLE\n");
        }
        else
            printf ("%s\n", strndup (node->start, node->length)); 
        //free (node);
    }
}