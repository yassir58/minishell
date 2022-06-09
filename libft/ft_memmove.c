/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:09:25 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/05 17:12:31 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src_ptr ;
	unsigned char	*dst_ptr ;
	int				i;

	i = 0;
	src_ptr = (unsigned char *)src;
	dst_ptr = (unsigned char *)dest;
	if (src_ptr == dst_ptr)
		return (dst_ptr);
	else if (src_ptr < dst_ptr)
	{
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	}
	else
	{
		while ((size_t)i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return ((void *)dest);
}
