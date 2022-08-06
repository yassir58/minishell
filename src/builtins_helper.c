/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:29:37 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 16:46:19 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_valid_option(char *option)
{
	int	i;

	i = 0;
	if (option[i] == '-')
	{
		i++;
		while (option [i] && option[i] == 'n')
			i++;
		if (option[i] == 0)
			return (1);
	}
	return (0);
}

int	cd_error(int err, char *arg)
{
	if (!err)
		return (builtin_err (" : Not a directory\n", arg));
	else
		return (builtin_err (": No such file or directory\n", arg));
	return (0);
}
