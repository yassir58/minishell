#include "../includes/minishell.h"


void push_node (lexer_node_t **head, lexer_node_t **tmp)
{
    lexer_node_t *node;
    lexer_node_t *temp;

    node = *head;
    temp = *tmp;
    if (!node)
        node = temp;
    else if (node && temp->joinable == TRUE)
    {
        node->length += temp->length;
        node->start = ft_strjoin (strndup (node->start, node->length)
            , strndup (temp->start, temp->length));
        node->token = temp->token;
        node->closed = temp->closed;
        free (temp);
    }
    else
    node->next = temp;
}