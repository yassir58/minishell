/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:22 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 19:26:14 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*update_prompt(t_shell_args *args)
{
	char	*pwd;
	char	**tab;
	char	*res;
	char	*elm;

	elm = ":\033[0;31m$ \033[0m";
	res = NULL;
	pwd = get_pwd (args->env_list);
	if (pwd && ft_strcmp (pwd, "/"))
	{
		tab = ft_split (pwd, '/');
		res = tab[number_of_el(tab) - 1];
		res = ft_strjoin (res, elm);
		free(pwd);
		free_tab (tab);
		return (res);
	}
	else
		return (ft_strjoin(pwd, elm));
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
