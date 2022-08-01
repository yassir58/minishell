/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:36:43 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/01 12:24:21 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    ft_unset(t_exec_node *exec_node, env_list_t **list)
{
    int i;
    int size;
    char **cmds;

    i = 1;
    cmds = get_commands(exec_node->cmd->cmds);
    size = number_of_el(cmds);
    g_data->exit_code = 0;
    while (i < size)
    {
        if (cmds[i] && !ft_isdigit(cmds[i][1]))
            delete_env_variable(list, cmds[i]);
        else
        {
            ft_putstr_fd("Minishell: unset: not a valid identifier\n", 2);
            g_data->exit_code = 1;
            return (1);
        }
        i++;
    }
    return (0);
}

int ft_env(t_exec_node *exec_node, env_list_t *list)
{
    char **cmds;

    cmds = get_commands(exec_node->cmd->cmds);
    if (number_of_el(cmds) == 1)
    {
        print_env_list(list);
        g_data->exit_code = 0;
    }
    else
    {
        g_data->exit_code = 1;
        ft_putstr_fd("Minishell: env: illegal option\n", 2);
        return (1);
    }
    return (0);
}  

void handle_exit(char **cmds)
{
    if (number_of_el(cmds) > 2)
    {
        ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
        g_data->exit_code = 1;
        return ;
    }
    else if (number_of_el(cmds) == 2)
    {
        if (is_number(cmds[1]))
        {
            g_data->exit_code = ft_atoi(cmds[1]);
            exit(g_data->exit_code);
        }
        else
        {
            g_data->exit_code = 255;
            printf("Minishell: exit: numeric argument required\n");
        }
    }
    exit(g_data->exit_code);
}

int ft_exit(t_exec_node *exec_node)
{
    char **cmds;

    cmds = get_commands(exec_node->cmd->cmds);
    g_data->exit_code = 0;
    printf("exit\n");
    handle_exit(cmds);
    return (1);
}

void    swap_nodes(env_list_t *a, env_list_t *b)
{
    char *key;
    char *value;
    int index;

    key = a->variable_name;
    value = a->value;
    index = a->index;
    a->variable_name = b->variable_name;
    a->value = b->value;
    a->index = b->index;
    b->variable_name = key;
    b->value = value;
    b->index = index;
}

int env_list_size(env_list_t *list)
{
    env_list_t *tmp;
    int i;

    i = 0;
    tmp = list;
    while (tmp != NULL)
    {
        i += 1;
        tmp = tmp->next;
    }
    return (i);
}

void    order_env_list(env_list_t *list)
{
    env_list_t *tmp_i;
    env_list_t *tmp_j;

    tmp_i = list;
    while (tmp_i != NULL)
    {
        tmp_j = tmp_i->next;
        while (tmp_j != NULL)
        {
            if (ft_strcmp(tmp_i->variable_name, tmp_j->variable_name) > 0)
                swap_nodes(tmp_i, tmp_j);
            tmp_j = tmp_j->next;
        }
        tmp_i = tmp_i->next;
    }
}

void    print_unsorted_env(env_list_t *list)
{
    int i;
    env_list_t *tmp;

    i = 1;
    tmp = list;
    while (tmp != NULL)
    {
        while (tmp != NULL)
        {
            if (i == tmp->index)
            {
                printf("%s=%s\n",tmp->variable_name, tmp->value);
                if (i == env_list_size(list))
                    break;
                i += 1;
            }
            else
                tmp = tmp->next;
        }
        if (i != env_list_size(list))
            tmp = list;
        else
        {
            if (tmp)
                tmp = tmp->next;
        }
    }
}

int    validate_export_args(char **cmds)
{
    int i;

    i = 1;
    while (cmds[i])
    {
        if (ft_isalpha(cmds[i][0]))
            i++;
        else
        {
            ft_putstr_fd("Minishell: export: not a valid identifier\n", 2);
            return (1);
        }
    }
    return (0);
}

int   check_existing_variable(char *argument, env_list_t *list)
{
    env_list_t *node;
    char **object;

    object = ft_split(argument, '=');
    if (object[0])
    {
        node = search_env_variable(object[0], list);
        if (node)
        {
            if (!object[1])
                return (-1);
            node->value = object[1];
            return (1);
        }
        else
        {
            if (!object[1])
                return (1);
        }
    }
    // free_string_table(object);
    return (0);
}

void    add_export_variable(char **cmds, env_list_t *list)
{
    int i;
    int tmp;
    
    i = 1;
    tmp = 0;
    while (cmds[i])
    {
        tmp = check_existing_variable(cmds[i], list);
        if (tmp != -1 && tmp != 1)
            push_env_node (&list, create_env_node (cmds[i], i));
        i++;
    }
}

void    ft_export(t_exec_node *exec_node, env_list_t *list)
{
    char **cmds;
    
    int i;

    i = 0;
    cmds = get_commands(exec_node->cmd->cmds);
    order_env_list(list);
    if (!cmds[1])
        print_export_list(list);
    else if (number_of_el(cmds) > 1)
    {
        if(!validate_export_args(cmds))
            add_export_variable(cmds, list);
    }
}
