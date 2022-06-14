#include "minishell.h"

/** GRAMMAR
 *  <EXP> : <COMMAND> { <PIPE> <COMMAND> }
 *  
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