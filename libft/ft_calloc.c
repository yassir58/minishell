/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:56:08 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/09 18:59:03 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*ptr;

	i = 0;
	ptr = malloc (count * size);
	if (ptr != NULL)
	{
		while (i < (count * size))
			((unsigned char *)ptr)[i++] = 0;
		return (ptr);
	}
	return (NULL);
}
