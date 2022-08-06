/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:22 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 17:00:59 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display(char **cmds)
{
	int	i;
	int	number;

	i = 0;
	number = number_of_el(cmds);
	while (i < number)
	{
		printf("File[%d]: %s\n", i, cmds[i]);
		i++;
	}
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	*prompt(char *string)
{
	char	*line;

	line = readline(string);
	if (line)
	{
		if (ft_strlen(line) > 0)
		{
			if (check_space(line))
				add_history(line);
			else
				line = prompt(string);
		}
		else
			line = prompt(string);
	}
	else
	{
		printf ("exit\n");
		exit(EXIT_SUCCESS);
	}
	return (line);
}
