/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:41 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 15:29:09 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_node(t_lexer_node *node, char *operator)
{
	if (node->token == OPERATOR)
	{
		if (!ft_strcmp(node->start, operator))
			return (1);
	}
	return (0);
}

int	check_redirect(t_lexer_node *node)
{
	if (node && node->token == OPERATOR)
	{
		if (!check_node(node, "|"))
			return (1);
	}
	return (0);
}

int	redirect_type(t_lexer_node *node)
{
	if (node && node->token == OPERATOR)
	{
		if (check_node(node, "<"))
			return (REDIRIN);
		else if (check_node(node, ">"))
			return (REDIROUT);
		else if (check_node(node, ">>"))
			return (APPEND);
		else if (check_node(node, "<<"))
			return (HEREDOC);
	}
	return (-1);
}
