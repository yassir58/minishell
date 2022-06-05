#include "../includes/minishell.h"




void push_node (lexer_node_t *node, lexer_node_t *temp)
{
    if (!node)
        node = temp;
    else if (node && temp->joinable == TRUE)
    {
        node->length += temp->length;
        node->joinable = TRUE;
        node->token = temp->token;
        node->closed = temp->closed;
        free (temp);
    }
    else
    node->next = temp;
}