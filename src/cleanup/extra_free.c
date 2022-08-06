/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:11:12 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 16:48:21 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*free_joined(char *str)
{
	char	*tmp;

	tmp = str;
	free(str);
	return (tmp);
}

void	free_tab(char *tab[])
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	free_list(t_lexer_node *node)
{
	t_lexer_node	*temp;
	t_lexer_node	*head;

	head = node;
	while (head)
	{
		temp = head;
		head = head->next;
		free (temp);
	}
}
