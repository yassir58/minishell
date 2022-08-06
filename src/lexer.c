/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 11:19:47 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 14:42:18 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer_node	*lexer (t_shell_args *args, char *line)
{
	int				index;
	t_lexer_node	*node;
	t_lexer_node	*tmp;

	(void)args;
	node = NULL;
	index = 0;
	while (line[index])
	{
		if (ft_strchr (OPERATORS, line[index]))
			tmp = handle_operator (line, &index);
		else if (ft_strchr (DELIMTERS, line[index]))
			tmp = handle_delim (line, &index);
		else
			tmp = handle_regular (line, &index);
		if (tmp)
			create_token_list (args, &node, tmp);
	}
	return (node);
}

t_lexer_node	*handle_regular(char *line, int *index)
{
	t_lexer_node *node;

    node = init_node ();
    node->start = &line[(*index)];
    node->token = WORD;
    node->next =  NULL;
    node->closed = 2;
    if (*index > 0 && line[(*index - 1)] != ' ' && !ft_strchr (OPERATORS, line[(*index - 1)])) 
        node->joinable = TRUE;
    while (!ft_strchr (DELIMTERS, line[(*index)]) 
        && !ft_strchr (OPERATORS, line[(*index)]))
    {
        node->length++;
        (*index)++;
    }
    return (node);
}

t_lexer_node *handle_delim (char *line, int *index)
{
	t_lexer_node *node;

	node = init_node ();
	if (line[(*index)] == ' ')
	{
		while (line[(*index)] && line[(*index)] == ' ')
			(*index)++;
	}
	else
	{
		handle_quote (line, index, &node);
		return (node);
	}
	free(node);
	return (NULL);
}

t_lexer_node *handle_operator (char *line, int *index)
{
	t_lexer_node *node;
	char operator;

	node = init_node();
	operator = line[(*index)];
	node->start = &(line[(*index)]);
	node->token = OPERATOR;
	if (line[(*index)] != '|')
	{
		while (line[(*index)] == operator)
		{
			node->length++;
			(*index)++;
		}
		if (node->length > 2)
			node->invalid = TRUE;
	}
	else
	{
		while (line[(*index)] == operator)
		{
			node->length++;
			(*index)++;
		}
		if (node->length > 1)
			node->invalid = TRUE;
	}
	return (node);
}

void handle_quote (char *line, int *index, t_lexer_node **node)
{
	char            delim;
	t_lexer_node    *tmp;

	tmp = *node;
	delim = line[(*index)];
	if (*index > 0 && line[(*index - 1)] != ' ' && !ft_strchr (OPERATORS, line[(*index - 1)])) 
		tmp->joinable = TRUE;
	(*index)++;
	tmp->start = &(line[(*index)]);
	while (line[(*index)] && line[(*index)] != delim)
	{
		(*index)++;
		tmp->length++;
	}
	if (delim == '\'')
		tmp->token = SINGLE_QUOTED_SEQUENCE;
	if (delim == '"')
		tmp->token = DOUBLE_QUOTED_SEQUENCE;
	if (line[(*index)] == delim)
	{
		 tmp->closed = TRUE;
		 (*index)++;
	}
	else
		tmp->closed = FALSE;
}
