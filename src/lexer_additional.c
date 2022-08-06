/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_additional.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:16:14 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 17:16:15 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token_list(t_shell_args *args, t_lexer_node **head, t_lexer_node *temp)
{
	t_lexer_node	*ptr;
	char			*tmp;

	ptr = *head;
	if (!args)
		return ;
	if (temp)
	{
		if (temp->joinable)
		{
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
		else
		{
			temp->start = ft_strndup (temp->start, temp->length);
			if (temp->token == DOUBLE_QUOTED_SEQUENCE || temp->token == WORD)
				temp->start = expand_variable (args, temp->start);
			push_to_list (head, temp);
		}
	}
}

void	check_word(t_lexer_node *tokens_list)
{
	t_lexer_node	*tmp;

	tmp = tokens_list;
	while (tmp)
	{
		if (tmp->token == DOUBLE_QUOTED_SEQUENCE || \
			tmp->token == SINGLE_QUOTED_SEQUENCE)
		{
			if (!ft_strchr (tmp->start, ' ') \
			&& !ft_strchr (tmp->start, '$'))
				tmp->token = WORD;
		}
		tmp = tmp->next;
	}
}

char	*expand_variable(t_shell_args *args, char *str)
{
	int		i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = get_variable_value (args, str, &i);
			if (tmp)
			{
				free_joined(res);
				res = ft_strjoin(res, tmp);
			}
			free(tmp);
		}
		else
			res = push_char (res, str[i++]);
	}
	free(str);
	return (res);
}

char	*extract_var_name(char *str, int *index)
{
	int		length;
	int		start;
	char	*var_name;

	length = 0;
	(*index)++;
	start = *index;
	var_name = NULL;
	while (str[*index] && str[*index] != ' ' && str[*index] != '\'' \
	&& str[*index] != '"' && str[*index] != '/')
	{
		if (str[(*index)] == '$')
			break ;
		length++;
		(*index)++;
	}
	if (length)
		var_name = strndup (&str[start], length);
	return (var_name);
}
