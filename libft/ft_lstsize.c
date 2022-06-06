/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:19:35 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/13 21:08:45 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*tmp_elem;

	size = 0;
	tmp_elem = lst;
	while (tmp_elem)
	{
		size++;
		tmp_elem = tmp_elem->next;
	}
	return (size);
}
