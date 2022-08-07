/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:14 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 19:12:09 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec_node	*new_exec_cmd(t_cmd_node *cmd, bool piped, bool status)
{
	t_exec_node	*node;

	node = (t_exec_node *)malloc(sizeof(t_exec_node));
	if (!node)
		return (NULL);
	node->cmd = cmd;
	if (node->cmd->cmds)
		node->builtin = is_builtin(cmd);
	else
		node->builtin = NULL;
	node->piped = piped;
	node->status = status;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_exec_node	*last_exec_node(t_exec_node *list)
{
	t_exec_node	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}
