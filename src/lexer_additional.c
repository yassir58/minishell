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
            ptr->start = ft_strjoin (strndup (ptr->start, ptr->length), strndup (temp->start, temp->length));
            ptr->length += temp->length;
            ptr->joinable = TRUE;
            ptr->closed = temp->closed ;
            if (ft_strchr (ptr->start, ' '))
                ptr->token = temp->token;
        }
        else
            push_to_list (head, temp);
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
            if (!ft_strchr (strndup (tmp->start, tmp->length), ' '))
                tmp->token = WORD;
        }
        tmp = tmp->next;
    }
}

void expand_variables (lexer_node_t *tokens_list)
{
    lexer_node_t *tmp;
    char *res;

    tmp = tokens_list;
    while (tmp)
    {
        if (tmp->token == DOUBLE_QUOTED_SEQUENCE)
        {
            res = handle_variables (strndup (tmp->start, tmp->length));
            printf ("--> %s \n", res);
            free (res);
        }
        tmp = tmp->next ;
    }
}

char *handle_variables (char *str)
{
    int i;
    char *res;
    char *tmp;

    i = 0;
    res = NULL;
    while (str[i])
    {
        if (str[i] == '$')
        {
            tmp = get_variable_value (str,  &i);
            if (tmp)
               res = ft_strjoin (res, tmp);
            printf ("res ==> %s \n", res);
        }
        else
        {
            res = push_char (res, str[i]);
            printf ("res =+=> %s \n", res);
        }
        i++;
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
        length++;
        if (str[(*index + 1)] == '$')
            break;
        (*index)++;
    }
    if (length)
        var_name = strndup (&str[start], length);
    return (var_name);
}
