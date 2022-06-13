#include "../includes/minishell.h"




void expand_single (lexer_node_t *head, lexer_node_t *temp)
{
    if (ft_strchr (head->start, '$') 
    && temp->token == SINGLE_QUOTED_SEQUENCE)
        head->start = handle_variables (head->start);
}