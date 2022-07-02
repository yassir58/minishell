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
   
    validate_first_node (node);
    validate_last_node (node);
    while (tmp)
    {
        invalid_operator (tmp);
        if (tmp->token == DOUBLE_QUOTED_SEQUENCE ||
            tmp->token == SINGLE_QUOTED_SEQUENCE)
        {
            if (tmp->closed == FALSE)
                syntax_error (node);
        }
        tmp = tmp->next;
    }
}

void validate_first_node (lexer_node_t *node)
{
    if (node->token == OPERATOR)
    {
        if (!ft_strcmp (node->start, "|"))
             syntax_error (node);
        else if (node->next == NULL)
            syntax_error (node);
    }
}

void invalid_operator (lexer_node_t *node)
{
    if (node->token == OPERATOR)
    {
        if (node->invalid == TRUE)
            syntax_error (node);
        if (ft_strcmp (node->start, "|"))
        {
            if (node->next && node->next->token == OPERATOR)
                syntax_error (node);
        }
        else if (node->next)
        {
            if (!ft_strcmp (node->next->start, "|"))
                syntax_error (node);
        }
    }
}

void validate_last_node (lexer_node_t *node)
{
    lexer_node_t *tmp ;

    tmp = node;
    while (tmp->next)
        tmp = tmp->next;
    if (tmp->token == OPERATOR)
        syntax_error (node);
}