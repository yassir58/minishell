/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:03:20 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/09 19:05:29 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	indx;
	size_t	res;

	src_len = 0;
	indx = 0;
	res = 0;
	dst_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (dst[dst_len] != '\0')
		dst_len++;
	if (dstsize > dst_len)
	{
		res = src_len + dst_len;
		while (dst_len < (dstsize - 1) && (src[indx] != '\0'))
			dst[dst_len++] = src[indx++];
		dst[dst_len] = '\0';
	}
	else
		res = src_len + dstsize;
	return (res);
}
