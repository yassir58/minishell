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


char *get_variable_value (char *str, int *i)
{
    char *varName;
    char *varValue;
    
    varName = extract_var_name (str, i);
    if (varName)
    {
        varValue = getenv (varName);
        free (varName);
    }
    return (varValue);
}

char *push_char (char *str, char c)
{
    int i;
    int length;
    char *res;

    i = 0;
    res = NULL;
    length = 0;
    if (str)
        length = ft_strlen (str);
    res = malloc (sizeof (char) * (length + 2));
    if (!res)
        return (NULL);
    while (i < length)
    {
        res[i] = str[i];
        i++;
    }
    res[i++] = c;
    res[i] = 0;
    if (str && length > 0)
        free (str);
    return (res);
}