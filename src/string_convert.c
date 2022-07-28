/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:15:02 by ochoumou          #+#    #+#             */
/*   Updated: 2022/07/28 12:12:33 by ochoumou         ###   ########.fr       */
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