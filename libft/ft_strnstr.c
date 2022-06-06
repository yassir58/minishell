/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:38:04 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/09 18:50:53 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j ;
	size_t	need_length;

	i = 0;
	j = 0;
	need_length = 0;
	while (needle[need_length] != 0)
		need_length++;
	while (i < len && haystack[i] != 0)
	{
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j]
				&& haystack[i + j] != '\0' && (i + j) < len)
				j++;
			if (j == need_length)
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	if (need_length == 0)
		return ((char *)haystack);
	return (NULL);
}
