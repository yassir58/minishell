/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 08:50:47 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/09 19:02:58 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{	
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j] != 0)
		j++;
	if (dstsize != 0)
	{
		while (i < (dstsize - 1) && (src[i] != 0))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (j);
}
