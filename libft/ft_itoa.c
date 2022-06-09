/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:04:07 by yelatman          #+#    #+#             */
/*   Updated: 2021/11/09 19:59:28 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	count_size(int nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		count++;
	}
	while (nbr != 0)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}

static void	fill(int nbr, char *str, int size)
{
	long long	nb ;
	int			rem ;

	rem = 0;
	nb = nbr;
	if (nb < 0)
	{
		nb = -nb ;
		str[0] = '-';
	}
	rem = nb;
	while (nb != 0)
	{
		rem = nb % 10;
		str[size--] = rem + 48 ;
		nb /= 10;
	}
}

char	*ft_itoa(int n)
{
	int				size ;
	char			*res;
	long long int	nbr;

	nbr = n;
	if (n == 0)
	{
		res = malloc(2 * sizeof(char));
		res[0] = 48;
		res[1] = '\0';
	}
	else
	{
		size = count_size(nbr);
		res = malloc ((size * sizeof(char)) + 1);
		if (!res)
			return (NULL);
		fill(n, res, (size - 1));
		res[size] = '\0';
	}
	return (res);
}
