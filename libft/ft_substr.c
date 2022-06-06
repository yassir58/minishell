/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:06:45 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/30 20:22:54 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	s_len;

	i = start;
	j = 0;
	s_len = 0;
	if (!s)
		return (NULL);
	while (s[s_len] != '\0')
		s_len++;
	if (s_len > start)
	{
		if ((s_len - start) < len)
			len = (s_len - start);
		substr = malloc((len + 1) * sizeof(char));
		if (!substr)
			return (NULL);
		while (j < len && s[i] != '\0')
			substr[j++] = s[i++];
		substr[j] = '\0';
		return (substr);
	}
	return (ft_strdup(""));
}
