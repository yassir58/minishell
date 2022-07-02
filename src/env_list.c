/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:04 by ochoumou          #+#    #+#             */
/*   Updated: 2022/07/02 14:14:05 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

env_list_t *search_env_variable(char *var, env_list_t *list)
{
    env_list_t *node;

    node = list;
    while (node != NULL)
    {
        if (node->next && !ft_strcmp(node->next->value, var))
            return (node);
        node = node->next;
    }
    return (NULL);
}

bool    delete_env_variable(char *var, env_list_t *list)
{
    env_list_t *tmp;
    env_list_t *node;

    if (node = search_env_variable(var, list))
    {
        node->next = node->next->next;
        free(node->next);
        return (TRUE);
    }
    return (FALSE);
}

void print_env_list (env_list_t *list)
{
    env_list_t *tmp;

    tmp = list;
    while (tmp)
    {
        printf("%s=%s\n", tmp->variable_name, tmp->value);
        tmp = tmp->next;
    }
}