#include "../includes/minishell.h"

int check_node(lexer_node_t *node, char *operator)
{
    if (node && node->token == 0)
    {
        if (ft_strcmp(node->start, operator) == 0)
            return (1);
    }
    return (0);
}

int check_redirect(lexer_node_t *node)
{
    if (node && node->token == OPERATOR)
    {
        if (!check_node(node, "|"))
            return (1);
    }
    return (0);
}

int redirect_type(lexer_node_t *node)
{
    if (node && node->token == OPERATOR)
    {
        if (check_node(node, "<"))
            return (REDIRIN);
        else if (check_node(node, ">"))
            return (REDIROUT);
        else if (check_node(node, ">>"))
            return (APPEND);
        else if (check_node(node, "<<"))
            return (HEREDOC);
    }
    return (-1);
}





