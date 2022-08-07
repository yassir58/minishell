/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:57 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 19:29:30 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_cmd_args(t_cmd **cmds, t_lexer_node **node)
{
	while (*node && ((*node)->token == WORD || \
	(*node)->token == DOUBLE_QUOTED_SEQUENCE || \
	(*node)->token == SINGLE_QUOTED_SEQUENCE))
	{
		add_command(cmds, new_command(ft_strdup((*node)->start)));
		(*node) = (*node)->next;
	}
}

t_exec_node	*check_piped(t_lexer_node **node, t_cmd *cmds, \
t_redirect *redirects)
{
	if (cmds && (*node))
	{
		if (check_node(*node, "|"))
		{
			(*node) = (*node)->next;
			return (new_exec_cmd(command_node(redirects, cmds), TRUE, FALSE));
		}
	}
	if ((*node) && check_node(*node, "|"))
		(*node) = (*node)->next;
	return (new_exec_cmd(command_node(redirects, cmds), FALSE, FALSE));
}

t_exec_node	*parse_command(t_shell_args *args, t_lexer_node **node)
{
	t_redirect	*redirects;
	t_redirect	*tmp;
	t_cmd		*cmds;

	cmds = NULL;
	tmp = NULL;
	redirects = NULL;
	while ((*node != NULL) && !check_node(*node, "|"))
	{
		parse_cmd_args(&cmds, node);
		if ((*node) && check_redirect((*node)))
		{
			tmp = add_redirect(&redirects, new_redirect(\
			ft_strdup((*node)->next->start), NULL, redirect_type((*node)), \
			(*node)->next->token));
			if (redirect_type((*node)) == HEREDOC)
			{
				if (!handle_ctrl(args, tmp, (*node)))
					return (new_exec_cmd(command_node(redirects, cmds), \
					TRUE, TRUE));
			}
			(*node) = (*node)->next->next;
		}
	}
	return (check_piped(node, cmds, redirects));
}

t_exec_node	*parse(t_shell_args *args, t_lexer_node *node)
{
	t_exec_node		*list;
	t_lexer_node	*token;

	token = node;
	list = NULL;
	if (!syntax_validation (args))
	{
		if (token && !check_node(node, "|"))
			list = parser_core(token, args);
	}
	return (list);
}

t_exec_node	*parser_core(t_lexer_node *token, t_shell_args *args)
{
	t_exec_node		*list;
	t_exec_node		*exec_node;
	t_exec_node		*last_node;

	list = NULL;
	while (token)
	{
		exec_node = parse_command(args, &token);
		if (exec_node->status)
			break ;
		if (!list)
		{
			exec_node->prev = NULL;
			list = exec_node;
		}
		else
		{
			last_node = last_exec_node(list);
			last_node->next = exec_node;
			exec_node->prev = last_node;
		}
	}
	return (list);
}
