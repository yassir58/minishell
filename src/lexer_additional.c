/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_additional.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:13:14 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 18:47:58 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token_list(t_shell_args *args, t_lexer_node **head, \
t_lexer_node *temp)
{
	t_lexer_node	*ptr;

	ptr = *head;
	if (!args)
		return ;
	if (temp)
	{
		if (temp->joinable)
			handle_joinable (args, ptr, temp);
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
