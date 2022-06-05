#include "../includes/minishell.h"

void	free_list(lexer_node_t *node)
{
	lexer_node_t	*temp;

	temp = node;
	while (temp->next)
        temp = temp->next;
    free (temp);
    if (node)
        free_list (node);
}


void print_token (int token)
{
    if (token == OPERATOR)
        printf ("OPERATOR \n");
    else if (token == WORD)
        printf ("WORD \n");
    else if (token == SINGLE_QUOTED_SEQUENCE)
        printf ("SINGLE_QUOTED_SEQUENCE \n");
    else
        printf ("DOUBLE_QUOTED_SEQUENCE \n");
}