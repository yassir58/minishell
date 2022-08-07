/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:38 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/07 11:34:42 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_exec_node(t_exec_node *list)
{
	t_exec_node	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		printf("===================================\n");
		if (tmp->builtin)
			printf("BUILTIN\n");
		if (tmp->piped)
			printf("PIPED\n");
		print_commands(tmp->cmd->cmds);
		if (tmp->cmd->redir_list)
			print_redirects(tmp->cmd->redir_list);
		tmp = tmp->next;
	}
}

void	print_redirects(t_redirect *list)
{
	t_redirect	*tmp;

	tmp = list;
	printf("Redirections:\n");
	while (tmp != NULL)
	{
		printf("Filename: %s\n", tmp->filename);
		if (tmp->type == APPEND)
			printf("Type: Append\n");
		else if (tmp->type == HEREDOC)
			printf("Type: Heredoc\n");
		else if (tmp->type == REDIRIN)
			printf("Type: Redir Input\n");
		else if (tmp->type == REDIROUT)
			printf("Type: Redir Output\n");
		printf("Filename Token: %d\n", tmp->token);
		if (tmp->hc)
			printf("Redirect Content: %s\n", tmp->hc);
		else
			printf("\n");
		tmp = tmp->next;
	}
}

void	print_commands(t_cmd *list)
{
	t_cmd	*tmp;
	int		i;

	tmp = list;
	i = 0;
	printf("Commands:\n");
	while (tmp != NULL)
	{
		printf("args[%d]: %s\n", i, tmp->cmd);
		tmp = tmp->next;
		i++;
	}
}
