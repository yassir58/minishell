#include "../includes/minishell.h"


void create_token_list (lexer_node_t **head, lexer_node_t *temp)
{
    lexer_node_t *node;
    lexer_node_t *ptr;

    node = *head;
    ptr = node;
    
    if (temp)
    {
        if (temp->joinable)
        {
            while (ptr->next)
                ptr = ptr->next;
            ptr->start = ft_strjoin (strndup (ptr->start, ptr->length), strndup (temp->start, temp->length));
            ptr->length += temp->length;
            ptr->joinable = TRUE;
            ptr->closed = temp->closed ;
            if (ft_strchr (ptr->start, ' '))
                ptr->token = temp->token;
        }
        else
            push_to_list (head, temp);
    }
}


void syntax_error (lexer_node_t *node)
{
    free_list (node);
    write (2, "Syntax error \n", 14);
    exit (EXIT_FAILURE);
}


void syntax_validation (lexer_node_t *node)
{
    lexer_node_t *tmp;

    if (node->token)
        syntax_error (node);
    tmp = node;
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