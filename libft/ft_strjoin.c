/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:22:28 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/01 18:54:57 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len) + 1);
	if (str != 0)
	{
		while (s1[++i] != 0)
			str[i] = s1[i];
		j = i;
		i = 0;
		while (s2[i] != 0)
			str[j++] = s2[i++];
		str[j] = 0;
		return (str);
	}
	return (0);
}