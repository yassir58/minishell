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
            expand_single (ptr, temp);
            temp->start = strndup (temp->start, temp->length);
            ptr->start = ft_strjoin (ptr->start, temp->start);
            ptr->length += temp->length;
            ptr->joinable = TRUE;
            ptr->closed = temp->closed;
            if (ft_strchr (ptr->start, ' '))
                ptr->token = temp->token;
        }
        else
        {
            temp->start = strndup (temp->start, temp->length);
            push_to_list (head, temp);
        }
    }
}

void check_word (lexer_node_t *tokens_list)
{
    lexer_node_t *tmp;

    tmp = tokens_list;
    while (tmp)
    {
        if (tmp->token == DOUBLE_QUOTED_SEQUENCE ||
            tmp->token == SINGLE_QUOTED_SEQUENCE)
        {
            if (!ft_strchr (tmp->start, ' ') 
            && !ft_strchr (tmp->start, '$'))
                tmp->token = WORD;
        }
        tmp = tmp->next;
    }
}

lexer_node_t *expand_variables (lexer_node_t *tokens_list)
{
    lexer_node_t *tmp;
    char *res;

    tmp = tokens_list;
    while (tmp)
    {
        if (tmp->token == DOUBLE_QUOTED_SEQUENCE ||
        (tmp->token == WORD && ft_strchr(tmp->start , '$')))
        {
            res = handle_variables (tmp->start);
            printf ("%s \n", res);
            free (tmp->start);
            tmp->start = res;
        }
        tmp = tmp->next ;
    }
    return (tokens_list);
}

char *handle_variables (char *str)
{
    int i;
    char *res;
    char *tmp;

    i = 0;
    res = "";
    while (str[i])
    {
        if (str[i] == '$')
        {
            tmp = get_variable_value (str,  &i);
            if (tmp)
               res = ft_strjoin (res, tmp);
        }
        else
        {
            res = push_char (res, str[i]);
            i++;
        }
    }
    return (res);
}

char *extract_var_name (char *str, int *index)
{
    int length; 
    char *var_name;
    int start;

    length = 0;
    (*index)++;
    start = *index;
    var_name = NULL;
    while (str[*index] && str[*index] != ' ')
    {
        if (str[(*index)] == '$')
            break;
        length++;
        (*index)++;
    }
    if (length)
        var_name = strndup (&str[start], length);
    return (var_name);
}
