#include "minishell.h"

/** GRAMMAR
 *  <EXP> : <COMMAND>
 *  <COMMAND> : <EXP> | <COMMAND>
 * */
int check_node_pipe(lexer_node_t *node)
{
    if (node->token == 0)
    {
        if (ft_strcmp(node->start, "|") == 0)
            return (1);
        else
            return (0);
    }
    else 
        return (0);
}

/** @Function:    Arguments_number
 *  @Description: The function bellow will help me find how many spots i should allcate for
 *  the arguments.
 * */

int arguments_number(lexer_node_t *node)
{
    int i;

    i = 0;
    while (node->next != NULL && !check_node_pipe(node))
    {
        i += 1;
        node = node->next;
    }
    return (i);
}

// Todo List:
// Handle CMD
// Handle PIPE
// Hanlde REDIR

t_ast_node *create_node(lexer_node_t *token)
{
    t_ast_node *tree_node;

    tree_node = (t_ast_node *)malloc(sizeof(t_ast_node));
    if (!tree_node);
        return (NULL);
    return (tree_node);
}