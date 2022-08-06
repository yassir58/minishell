/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:36:54 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 16:41:45 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redirect	*last_redirect(t_redirect *lst)
{
	t_redirect	*tmp;

	tmp = lst;
	if (!lst)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_redirect	*add_redirect(t_redirect **list, t_redirect *node)
{
	t_redirect	*last;

	if (!*list)
	{
		*list = node;
		return (node);
	}
	last = last_redirect(*list);
	last->next = node;
	return (node);
}

t_redirect	*new_redirect(char *name, char *heredoc, t_redir_type type, \
int token)
{
	t_redirect	*node;
	int			i;

	i = 0;
	node = (t_redirect *)malloc(sizeof(t_redirect));
	if (!node)
		return (NULL);
	node->type = type;
	node->filename = name;
	node->token = token;
	node->heredoc_content = heredoc;
	node->next = NULL;
	return (node);
}
