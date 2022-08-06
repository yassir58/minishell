/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:15:02 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 11:51:06 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int commands_number(t_cmd *list)
{
    t_cmd   *tmp;
    int     i;

    i = 0;
    tmp = list;
    if (!list)
        return (0);
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

int env_size(t_env_list *list)
{
    t_env_list   *tmp;
    int     i;

    i = 0;
    tmp = list;
    if (!list)
        return (0);
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

char    **get_commands(t_cmd *cmds)
{
    t_cmd *tmp;
    int i;
    char **commands;

    i = 0;
    tmp = cmds;
    commands = (char **)malloc(sizeof(char *) * (commands_number(cmds) + 1));
    if (!commands)
        return (NULL);
    while (tmp)
    {
        commands[i++] = ft_strdup(tmp->cmd);
        tmp = tmp->next;
    }
    commands[i] = NULL;
    return (commands);
}

char    **get_env_table(t_env_list *list)
{
    t_env_list *tmp;
    int i;
    char **env_table;
    char *row;

    i = 0;
    tmp = list;
    env_table = (char **)malloc(sizeof(char *) * (env_size(list) + 1));
    if (!env_table)
        return (NULL);
    while (tmp)
    {
        row = ft_strdup(tmp->variable_name);
        row = ft_strjoin(row, "=");
        env_table[i++] = ft_strjoin(row, tmp->value);
        tmp = tmp->next;
    }
    env_table[i] = NULL;
    return (env_table);
}

int number_of_el(char **cmds)
{
    int i;

    i = 0;
    while (cmds[i] != NULL)
        i++;
    return (i);
}

void    display(char **cmds)
{
    int i;
    int number;

    i = 0;
    number = number_of_el(cmds);
    while (i < number)
    {
        printf("File[%d]: %s\n",i,cmds[i]);
        i++;
    }
}