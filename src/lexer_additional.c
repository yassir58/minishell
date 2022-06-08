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