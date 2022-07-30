/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:13:56 by ochoumou          #+#    #+#             */
/*   Updated: 2022/07/28 12:18:50 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd *new_command(char *cmd)
{
    t_cmd *node;

    node = (t_cmd *)malloc(sizeof(t_cmd));
    if(!node)
        return (NULL);
    node->cmd = cmd;
    node->next = NULL;
    return (node);
}

void    add_command(t_cmd **list, t_cmd *cmd)
{
    t_cmd *lst_node;

    if (!*list)
    {
        *list = cmd;
        return ;
    }
    lst_node = last_command(*list);
    lst_node->next = cmd;
}

t_cmd *last_command(t_cmd *lst)
{
    t_cmd *tmp;

    tmp = lst;
    if (!lst)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}

t_cmd_node *command_node(t_redirect *redirlist, t_cmd *cmdlist)
{
    t_cmd_node *node;

    node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
    if (!node)
        return (NULL);
    node->cmds = cmdlist;
    node->redir_list = redirlist;
    return (node);
}
