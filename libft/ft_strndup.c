/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:09:52 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 17:11:57 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;
	char	*new;

	i = 0;
	str = (char *)s;
	new = (char *)malloc((sizeof(char) * (n + 1)));
	if (!new)
		return (NULL);
	while (s[i] != '\0' && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
