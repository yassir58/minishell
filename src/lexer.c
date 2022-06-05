#include "../includes/minishell.h"


lexer_node_t *lexer (char *line)
{
    int index;
    lexer_node_t *node;
    lexer_node_t *tmp;
    node = NULL;

    while (line[index])
    {
        if (ft_strchr (DELIMTERS, line[index]) || ft_strchr (OPERATORS, line[index]))
            tmp = handle_delim (line, &index);
        else
            tmp = handle_regular (line, &index);
        push_node (node, tmp);
    }
    return (SV_NODEFER);
}

lexer_node_t *handle_regular (char *line, int *index)
{
    lexer_node_t *node;

    node = malloc (sizeof (lexer_node_t));
    if (!node)
        return (NULL);
    ft_memset (node, 0, sizeof(node));
    node->start = line[(*index)];
    node->token = WORD;
    node->next =  NULL;
    while (!ft_strchr (DELIMTERS, line[(*index)]))
    {
        node->length++;
        (*index)++;
    }
    return (node);
}

lexer_node_t *handle_delim (char *line, int *index)
{
    lexer_node_t *node;

    node = malloc (sizeof (lexer_node_t));
    if (!node)
        return (NULL);
    ft_memset (node, 0, sizeof (node));
    if (ft_strchr (DELIMTERS, line[(*index)]))
    {
        if (line[(*index)] == ' ')
        {
            while (line[(*index)] && line[(*index)] == ' ')
                (*index)++;
        }
        else
           handle_quotes (line, &index, node);
    }
    else if (ft_strchr (OPERATORS, line[(*index)]))
        handle_operator(line, &index, node);
    return (node);
}

void handle_operator (char *line, int *index, lexer_node_t *node)
{
    node->start = line[(*index)];
    node->length = 1;
    node->token = OPERATOR;
    node->next = NULL;
}

void handle_quote (char *line, int *index, lexer_node_t *node)
{
    char delim;

    delim = line [(*index)];
    if (line[(*index - 1)] != ' ')
        node->joinable = TRUE;
    (*index)++;
    node->start = line[(*index)];
    while (line[(*index)] && line[(*index)] != delim)
    {
        (*index)++;
        node->length++;
    }
    if (delim == '\'')
        node->token = SINGLE_QUOTED_SEQUENCE;
    if (delim == '"')
        node->token = DOUBLE_QUOTED_SEQUENCE;
    if (line[(*index)] == delim)
        node->closed = TRUE;
    else
        node->closed = FALSE;
}
