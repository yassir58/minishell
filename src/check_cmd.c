/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 14:45:04 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/02 12:22:41 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

char	**paths_table(char *path)
{
	char	**paths;

	paths = ft_split(path, ':');
	return (paths);
}

char	*check_access(shell_args_t *args, char *command, char *path, int *status)
{
	char **paths;
	int 	i;
	char	*temp;
	char *spath;

	i = 0;
	spath = get_env_path (args);
	if (path)
	{
		temp = command;
		if (access_status(temp, status) == 0)
			return (temp);
	}
	else
	{
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

	rt_status = 0;
	if (access (cmd, F_OK) != -1)
	{
		*status = 0;
		if (access (cmd , (F_OK | X_OK)) != -1)
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


char *get_env_path (shell_args_t *args)
{
	env_list_t *temp;
	
	temp = args->env_list;
	while (temp)
	{
		if (!ft_strcmp (temp->variable_name, "SPATH"))
			return (ft_strdup (temp->value));
		temp = temp->next;
	}
	return (NULL);
}