/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:04:05 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 15:07:29 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (ft_strlen(str) == 1)
			return (0);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	swap_nodes(t_env_list *a, t_env_list *b)
{
	char	*key;
	char	*value;
	int		index;

	key = a->variable_name;
	value = a->value;
	index = a->index;
	a->variable_name = b->variable_name;
	a->value = b->value;
	a->index = b->index;
	b->variable_name = key;
	b->value = value;
	b->index = index;
}
