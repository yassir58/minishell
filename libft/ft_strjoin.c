/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:22:28 by yelatman          #+#    #+#             */
/*   Updated: 2022/07/22 10:57:22 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*ft_strcat(char *dest, char const *src)
{
	int	i;
	int	dstlen;

	i = 0;
	dstlen = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[dstlen + i] = src[i];
		i++;
	}
	dest[dstlen + i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = (char *)malloc((sizeof(char) * s1len + s2len + 1));
	if (!str)
		return (NULL);
	str[0] = '\0';
	if (s1)
		ft_strcat(str, s1);
	if (s2)
		ft_strcat(str, s2);
	return (str);
}