/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:56:26 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/11 14:59:28 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != 0)
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (res != 0)
	{
		i = 0;
		while (s[i] != 0)
		{
			res[i] = f(i, s[i]);
			i++;
		}
		res[i] = 0;
		return (res);
	}
	return (0);
}
