/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:04 by ochoumou          #+#    #+#             */
/*   Updated: 2022/07/28 18:44:55 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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


void deleteNode(env_list_t **list, char *key)
{
    env_list_t *tmp;
    env_list_t *prev;

    tmp = *list;
    printf("Zaba: %s\n", (*list)->variable_name);
    printf("Zaba addres: %p\n", *list);
    if (tmp != NULL && (ft_strcmp(tmp->variable_name, key) == 0))
    {
        *list = tmp->next;
        free(tmp);
        printf("hoho\n");
        return;
    }
    printf("Sbrdida\n");
    
    while (tmp != NULL && (ft_strcmp(tmp->variable_name, key) != 0))
    { 
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}

env_list_t *search_env_variable(char *var, env_list_t *list)
{
    env_list_t *node;

    node = list;
    while (node != NULL)
    {
        if (ft_strcmp(node->variable_name, var) == 0)
            return (node);
        node = node->next;
    }
    return (NULL);
}

void    delete_env_variable(char *var, env_list_t *list)
{
    env_list_t *tmp;
    env_list_t *node;

    
    deleteNode(&list, var);
    printf("%s\n", list->variable_name);
}




