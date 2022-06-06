/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:08:39 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/13 21:31:35 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*head;
	t_list	*tmp_elem;

	head = lst;
	new_list = NULL;
	while (head != NULL)
	{
		tmp_elem = ft_lstnew(f(head->content));
		if (tmp_elem == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, tmp_elem);
		head = head->next;
	}
	return (new_list);
}
