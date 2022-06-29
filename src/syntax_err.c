#include "../includes/minishell.h"



void syntax_error (lexer_node_t *node)
{
    write (2, "Syntax error \n", 14);
    free_list (node);
    exit (EXIT_FAILURE);
    
}

void syntax_validation (lexer_node_t *node)
{
    lexer_node_t *tmp;

    tmp = node ;
    if (node->token == OPERATOR)
        syntax_error (node);
    while (tmp)
    {
        if (tmp->token == DOUBLE_QUOTED_SEQUENCE ||
            tmp->token == SINGLE_QUOTED_SEQUENCE)
        {
            if (tmp->closed == FALSE)
                syntax_error (node);
        }
        tmp = tmp->next;
    }
}
