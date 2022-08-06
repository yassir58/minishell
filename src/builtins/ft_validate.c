/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:04:10 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 15:09:33 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_args(char *cmds, char *filter)
{
	int	i;

	i = 0;
	if (ft_isdigit(cmds[i]))
		return (0);
	while (cmds[i])
	{
		if (ft_isalpha(cmds[i]) || ft_isdigit(cmds[i]) || \
		ft_strchr(filter, cmds[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	validate_export_args(char **cmds)
{
	int	i;

	i = 1;
	while (cmds[i])
	{
		if (validate_args(cmds[i], "_="))
			i++;
		else
		{
			ft_putstr_fd("Minishell: export: not a valid identifier\n", 2);
			return (1);
		}
	}
	return (0);
}
