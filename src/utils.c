/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:45:28 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 17:25:47 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer_node	*init_node(void)
{
	t_lexer_node	*node;

	node = malloc (sizeof (t_lexer_node));
	if (!node)
		return (NULL);
	node->closed = 0;
	node->invalid = 0;
	node->joinable = 0;
	node->length = 0;
	node->start = 0;
	node->next = NULL;
	node->token = 0;
	return (node);
}

void	push_to_list(t_lexer_node **head, t_lexer_node *node)
{
	t_lexer_node	*temp;

	temp = *head;
	if (node)
	{
		if (*head == NULL)
			*head = node;
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = node;
		}
	}
}

char	*get_variable_value(t_shell_args *args, char *str, int *i)
{
	char	*key;
	char	*value;

	value = NULL;
	key = extract_var_name (str, i);
	if (key)
	{
		if (!ft_strcmp (key, "?"))
			value = ft_itoa (g_data->exit_code);
		else
			value = ft_getenv (args, key);
		free (key);
	}
	return (value);
}

char	*push_char(char *str, char c)
{
	int		i;
	int		length;
	char	*res;

	i = 0;
	res = NULL;
	length = 0;
	if (str)
		length = ft_strlen (str);
	res = malloc (sizeof (char) * (length + 2));
	if (!res)
		return (NULL);
	while (i < length)
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = c;
	res[i] = 0;
	if (str)
		free (str);
	return (res);
}

char	*ft_getenv(t_shell_args *args, char *varName)
{
	t_env_list	*temp;

	temp = args->env_list;
	while (temp)
	{
		if (!ft_strcmp (temp->variable_name, varName))
			return (ft_strdup (temp->value));
		temp = temp->next;
	}
	return (NULL);
}
