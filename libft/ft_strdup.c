/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:40:14 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/09 18:59:33 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*res ;
	int		len ;
	int		i;

	i = 0;
	len = 0;
	while (s1[len] != 0)
		len++;
	res = malloc((len * sizeof(char)) + 1);
	if (res != 0)
	{
		while (s1[i] != 0)
		{
			res[i] = s1[i];
			i++;
		}
		res[i] = 0;
		return (res);
	}
	return (0);
}
