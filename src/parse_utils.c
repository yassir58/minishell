/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:47 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 15:32:27 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	advanced_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s2[i])
	{
		if ((s1[i] == s2[i] || s1[i] == s2[i] + 32 || s2[i] == s1[i] + 32))
			i++;
		else
			return (1);
	}
	return (0);
}

bool	is_builtin(t_cmd_node *cmd)
{
	char	*arg;

	arg = cmd->cmds->cmd;
	if (!advanced_strcmp(arg, "echo") || !advanced_strcmp(arg, "cd") \
	|| !advanced_strcmp(arg, "pwd") || !advanced_strcmp(arg, "export") \
	|| !advanced_strcmp(arg, "unset") ||!advanced_strcmp(arg, "env") || \
	!advanced_strcmp(arg, "exit"))
		return (true);
	return (false);
}

int	count_filenames(t_lexer_node *node)
{
	int	i;

	i = 0;
	while (node && node->token != OPERATOR)
	{
		i += 1;
		node = node->next;
	}
	return (i);
}

char	**filenames_table(t_lexer_node **node, int files)
{
	int		i;
	char	**filenames;

	i = 0;
	filenames = (char **)malloc(sizeof(char *) * (files + 1));
	if (!filenames)
		return (NULL);
	if (files == 1)
	{
		filenames[i++] = ft_strdup((*node)->next->start);
		(*node) = (*node)->next->next;
	}
	else
	{
		while (i < files)
		{
			filenames[i++] = ft_strdup((*node)->start);
			(*node) = (*node)->next;
		}
	}
	filenames[i] = NULL;
	return (filenames);
}
