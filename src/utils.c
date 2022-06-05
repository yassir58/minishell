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


void testing (lexer_node_t *node)
{
    printf (" __________________ lexer output __________________\n");
    if (!node)
        printf ("NULL ==> \n");
    else
    {
        write (1, node->start, node->length);
        write (1, "\n", 1);
        print_token (node->token);
        free (node);
    }
}