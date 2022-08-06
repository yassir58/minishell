/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:45:04 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 19:14:55 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**paths_table(char *path)
{
	char	**paths;

	paths = ft_split(path, ':');
	return (paths);
}

char	*check_access(t_shell_args *args, char *command, char *path, \
int *status)
{
	int		i;
	char	*temp;
	char	*spath;

	i = 0;
	temp = NULL;
	spath = get_env_path (args);
	if (path)
	{
		temp = command;
		if (access_status(temp, status) == 0)
			return (temp);
	}
	else
		temp = cmd_with_no_path (spath, status, command);
	return (temp);
}

int	access_status(char *cmd, int *status)
{
	int			rt_status;
	struct stat	sfile;

	rt_status = 0;
	if (access (cmd, F_OK) != -1)
	{
		*status = 0;
		if (access (cmd, (F_OK | X_OK)) != -1)
		{
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

char	*get_env_path(t_shell_args *args)
{
	t_env_list	*temp;

	temp = args->env_list;
	while (temp)
	{
		if (!ft_strcmp (temp->variable_name, "SPATH"))
			return (ft_strdup (temp->value));
		temp = temp->next;
	}
	return (NULL);
}

char	*cmd_with_no_path(char *spath, int *status, char *command)
{
	int		i;
	char	**paths;
	char	*temp;

	i = 0;
	temp = NULL;
	paths = NULL;
	if (!spath)
	{
		*status = 127;
		return (NULL);
	}
	paths = paths_table(spath);
	while (paths[i])
	{
		temp = ft_strjoin(ft_strjoin(paths[i], "/"), command);
		if (access_status (temp, status) == 0 && ft_strcmp(command, ""))
			break ;
		else
			free(temp);
		i++;
	}
	free_tab(paths);
	return (temp);
}
