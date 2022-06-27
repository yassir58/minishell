/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:45:04 by yelatman          #+#    #+#             */
/*   Updated: 2022/06/27 15:15:03 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char	**paths_table(char *path)
{
	char	**paths;

	paths = ft_split(path, ':');
	return (paths);
}

char	*check_access(char *command)
{
	char **paths;
	int 	i;
	char	*temp;

	i = 0;
	paths = paths_table(_PATH_STDPATH);
	while (paths[i])
	{
		temp = ft_strjoin(ft_strjoin(paths[i], "/"), command);
		if (access(temp, (F_OK & X_OK)) != -1)
		{
			free_tab(paths);
			return (temp);
		}
		else
			free(temp);
		i++;
	}
	free_tab(paths);
	return (NULL);
}