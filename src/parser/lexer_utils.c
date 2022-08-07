/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:13:24 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 19:20:58 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	escape_char(char *line, int *indx, int *length, char operator)
{
	while (line[(*indx)] && line[(*indx)] == operator)
	{
		(*length)++;
		(*indx)++;
	}
}

void	increment_indx(char *line, int *index, int *length, char delim)
{
	while (line[(*index)] && line[(*index)] != delim)
	{
		(*index)++;
		(*length)++;
	}
}

void	handle_joinable(t_shell_args *args, t_lexer_node **joinable, \
t_lexer_node *temp)
{
	t_lexer_node	*ptr;
	char			*tmp;

	ptr = *joinable;
	while (ptr->next)
		ptr = ptr->next;
	temp->start = ft_strndup(temp->start, temp->length);
	if (temp->token == DOUBLE_QUOTED_SEQUENCE || temp->token == WORD)
		temp->start = expand_variable (args, temp->start);
	if (ptr->token == DOUBLE_QUOTED_SEQUENCE || ptr->token == WORD)
		ptr->start = expand_variable (args, ptr->start);
	tmp = ft_strjoin (ptr->start, temp->start);
	free(ptr->start);
	ptr->start = tmp;
	free(temp->start);
	ptr->length += temp->length;
	ptr->joinable = TRUE;
	ptr->closed = temp->closed;
	if (ft_strchr (ptr->start, ' '))
		ptr->token = temp->token;
	free(temp);
}
