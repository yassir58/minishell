/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_additional.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:13:14 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 12:13:15 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void create_token_list (shell_args_t *args, lexer_node_t **head, lexer_node_t *temp)
{
    lexer_node_t *node;
    lexer_node_t *ptr;
    char *tmp;

    node = *head;
    ptr = node;
    if (!args)
        return ;
    if (temp)
    {
        if (temp->joinable)
        {
            while (ptr->next)
                ptr = ptr->next;
            temp->start = strndup (temp->start, temp->length); // ft_strndup // UNAUTHORIZED FUNCTION.
            if (temp->token == DOUBLE_QUOTED_SEQUENCE || temp->token == WORD)
                temp->start = expand_variable (args, temp->start);
            if (ptr->token == DOUBLE_QUOTED_SEQUENCE || ptr->token == WORD)
                ptr->start = expand_variable (args, ptr->start);
            tmp = ft_strjoin (ptr->start, temp->start);
            // Refactor the free up function here.
            free(ptr->start);
            free(temp->start);
            ptr->start = tmp;
            ptr->length += temp->length;
            ptr->joinable = TRUE;
            ptr->closed = temp->closed;
            if (ft_strchr (ptr->start, ' '))
                ptr->token = temp->token;
            free(temp);
        }
        else
        {
            temp->start = strndup (temp->start, temp->length);
            if (temp->token == DOUBLE_QUOTED_SEQUENCE || temp->token == WORD)
                temp->start =  expand_variable (args, temp->start);
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

char *expand_variable (shell_args_t *args, char *str)
{
    int i;
    char *res;
    char *tmp;
    char *sed;

    i = 0;
    res = ft_strdup("");
    while (str[i])
    {
        if (str[i] == '$')
        {
            tmp = get_variable_value (args, str,  &i);
            if (tmp)
            {
               sed = ft_strjoin (res, tmp);
               // Refactor this free function.
               free(res);
               res = sed;
            }
            free(tmp);
        }
        else
        {
            res = push_char (res, str[i]);
            i++;
        }
    }
    free(str);
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
    while (str[*index] && str[*index] != ' ' && str[*index] != '\'' && str[*index] != '"' && str[*index] != '/')
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
