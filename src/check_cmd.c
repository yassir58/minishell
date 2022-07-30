/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:45:04 by yelatman          #+#    #+#             */
/*   Updated: 2022/07/29 11:23:31 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char	**paths_table(char *path)
{
	char	**paths;

	paths = ft_split(path, ':');
	return (paths);
}

char	*check_access(char *command, char *path, int *status)
{
	char **paths;
	int 	i;
	char	*temp;

	i = 0;
	if (path)
	{
		temp = command;
		if (access_status(temp, status) == 0)
			return (temp);
	}
	else
	{
		paths = paths_table(_PATH_STDPATH);
		while (paths[i])
		{
			temp = ft_strjoin(ft_strjoin(paths[i], "/"), command);
			if (access_status (temp, status) == 0 && ft_strcmp(command, ""))
			{
				free_tab(paths);
				return (temp);
			}	
			else
				free(temp);
			i++;
		}
		free_tab(paths);	
	}
	return (NULL);
}

int access_status (char *cmd, int *status)
{
	int rt_status;
	struct stat sfile;
	
	if (access (cmd, F_OK) != -1)
	{
			if (access (cmd, (F_OK & X_OK)) != -1)
			{
				*status = 0;
				stat (cmd, &sfile);
				if (S_ISDIR(sfile.st_mode) == 1)
				*status = -126;	
			}
			else
				*status = 126;
	}
	else 
		*status = 127;
	rt_status = *status;
	return (rt_status);
}