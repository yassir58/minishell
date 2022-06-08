/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:39:37 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/13 21:30:10 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*head;

	if (lst)
	{	
		head = *lst;
		if (!(*lst))
			(*lst) = new;
		else
		{
			while (head->next != NULL)
				head = head->next;
			head->next = new;
		}
	}
}
