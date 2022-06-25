#include "../includes/minishell.h"

lexer_node_t *lexer (char *line)
{
    int index;
    lexer_node_t *node;
    lexer_node_t *tmp;
    lexer_node_t *pointer;

    node = NULL;
    index = 0;
    while (line[index])
    {
        if (ft_strchr (OPERATORS, line[index]))
            tmp = handle_operator (line, &index);
        else if (ft_strchr (DELIMTERS, line[index]))
            tmp = handle_delim (line, &index);
        else
            tmp = handle_regular (line, &index);
        if (tmp)
        {
            create_token_list (&node, tmp);
            // printf ("tmp exist \n");
        }
    }
    return (node);
}

lexer_node_t *handle_regular (char *line, int *index)
{
    lexer_node_t *node;


    node = init_node ();
    node->start = &line[(*index)];
    node->token = WORD;
    node->next =  NULL;
    while (!ft_strchr (DELIMTERS, line[(*index)]) 
        && !ft_strchr (OPERATORS, line[(*index)]))
    {
        // printf ("regular char %c at %d \n", line [(*index)], (*index));
        node->length++;
        (*index)++;
    }
    return (node);
}

lexer_node_t *handle_delim (char *line, int *index)
{
    lexer_node_t *node;

    node = init_node ();
    if (line[(*index)] == ' ')
    {
        while (line[(*index)] && line[(*index)] == ' ')
        {
            // printf ("%d escaping space \n", (*index));
            (*index)++;
        }
    }
    else
    {
         handle_quote (line, index, &node);
         return (node);
    }
    return (NULL);
}

lexer_node_t *handle_operator (char *line, int *index)
{
    lexer_node_t *node;
    char operator;

    node = init_node();
    operator = line[(*index)];
    node->start = &(line[(*index)]);
    node->token = OPERATOR;
    if (line[(*index)] != '|')
    {
        while (line[(*index)] == operator)
        {
            node->length++;
            (*index)++;
        }
        if (node->length > 2)
            node->invalid = TRUE;
    }
    else
    {
        while (line[(*index)] == operator)
        {
            node->length++;
            (*index)++;
        }
        if (node->length > 1)
            node->invalid = TRUE;
    }
    return (node);
}

void handle_quote (char *line, int *index, lexer_node_t **node)
{
    char            delim;
    lexer_node_t    *tmp;

    tmp = *node;
    delim = line[(*index)];
    if (*index > 0 && line[(*index - 1)] != ' ')
        tmp->joinable = TRUE;
    (*index)++;
    tmp->start = &(line[(*index)]);
    while (line[(*index)] && line[(*index)] != delim)
    {
        (*index)++;
        tmp->length++;
    }
    if (delim == '\'')
        tmp->token = SINGLE_QUOTED_SEQUENCE;
    if (delim == '"')
        tmp->token = DOUBLE_QUOTED_SEQUENCE;
    if (line[(*index)] == delim)
    {
         tmp->closed = TRUE;
         (*index)++;
    }
    else
        tmp->closed = FALSE;
    // printf ("______ %d _____ \n", tmp->length);
}
