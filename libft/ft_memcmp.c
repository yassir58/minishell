/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 12:49:33 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/09 18:58:20 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*sp1;
	unsigned char	*sp2;

	sp1 = (unsigned char *) s1;
	sp2 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (sp1[i] != sp2[i])
		{
			return (sp1[i] - sp2[i]);
		}
		i++;
	}
	return (0);
}
