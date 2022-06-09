/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:01:26 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/13 21:21:22 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*delete;

	while ((*lst) != NULL)
	{
		delete = (*lst);
		(*lst) = (*lst)->next;
		ft_lstdelone(delete, del);
	}
	lst = NULL;
}
