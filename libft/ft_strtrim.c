/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 19:09:33 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 17:57:33 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	check(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	allocate(char const *str, char const *set, int *start)
{
	int		i;

	i = 0;
	while (check(str[i], set))
		i++;
	*start = i;
	while (str[i])
		i++;
	i--;
	while (i >= 0 && check(str[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		len;
	int		start;
	int		end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = allocate(s1, set, &start);
	len = end - start + 1;
	res = ft_substr(s1, start, len);
	return (res);
}
