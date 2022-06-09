#include "../includes/minishell.h"

void	free_list(lexer_node_t *node)
{
	lexer_node_t	*temp;
    lexer_node_t    *head;

	head = node;
	while (head)
    {
        temp = head;
        head = head->next;
        free (temp);
    }
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
        print_token (node->token);
        if (node->joinable)
        {
            printf ("%s \n", node->start);
            printf ("JOINABLE\n");
        }
        else
            printf ("%s\n", strndup (node->start, node->length)); 
        //free (node);
    }
}

lexer_node_t *init_node ()
{
    lexer_node_t *node;

    node = malloc (sizeof (lexer_node_t));
    if (!node)
        return (NULL);
    node->closed = 0;
    node->invalid = 0;
    node->joinable = 0;
    node->length = 0;
    node->start = 0;
    node->next = NULL;
    node->token = 0;
    return (node);
}

void push_to_list (lexer_node_t **head, lexer_node_t *node)
{
    lexer_node_t *temp;

    temp = *head;
    if (node)
    {
        if (*head == NULL)
            *head = node;
        else
        {
            while (temp->next)
                temp = temp->next;
           temp->next = node; 
        }
    }
}