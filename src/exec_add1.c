/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_add1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:45:29 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 15:39:22 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**handle_absolue_path(char **path_table)
{
	char	**cmd_path;
	char	*dir_name;
	int		i;

	i = 0;
	dir_name = NULL;
	cmd_path = malloc (sizeof (char *) * 3);
	if (!cmd_path)
		allocation_err ();
		cmd_path[2] = NULL;
	cmd_path[0] = ft_strdup ("");
	while (path_table[i])
	{
		if (!path_table[i + 1])
			break ;
		dir_name = ft_strjoin ("/", path_table[i]);
		cmd_path[0] = ft_strjoin (cmd_path[0], dir_name);
		i++;
	}
	cmd_path[1] = ft_strdup (path_table[i]);
	return (cmd_path);
}

char	**handle_relative_path(char **path_table)
{
	char	**cmd_path;
	char	*dir_name;
	int		i;

	i = 0;
	dir_name = NULL;
	cmd_path = malloc (sizeof (char *) * 3);
	if (!cmd_path)
		allocation_err ();
	cmd_path[2] = NULL;
	cmd_path[0] = ft_strdup ("");
	while (path_table[i])
	{
		if (!path_table[i + 1])
			break ;
		if (!i)
			dir_name = path_table[i];
		else
			dir_name = ft_strjoin ("/", path_table[i]);
		cmd_path[0] = ft_strjoin (cmd_path[0], dir_name);
		i++;
	}
	cmd_path[1] = ft_strdup (path_table[i]);
	return (cmd_path);
}

int	handle_simple_command(shell_args_t *args)
{
	int	status;
	int	in;
	int	out ;

	status = 0;
	in = 0;
	out = 1;
	if (args->exec_node->builtin)
		status = handle_one_builtin_cmd (args, in, out);
	else
		status = handle_non_builtin (args, &in, &out);
	return (status);
}

int	handle_non_builtin(shell_args_t *args, int *in, int *out)
{
	int	id;
	int	status;

	id = 0;
	status = 0;
	id = fork_child (args);
	if (id == 0)
	{
		status = handle_redirections (args, args->exec_node, in, out);
		if (status)
			exit (status);
		link_rediriction_pipes (*in, *out);
		exec_command (args, args->exec_node);
	}
	else
		g_data->fork_status = id;
	return (status);
}

void	shell_err(char *command, int status, int path_check)
{
	if (status == -126)
	{
		status = 126;
		ft_putstr_fd (ft_strjoin (command, ": is a directory\n"), STDERR_FILENO);
	}
	else if (status == 127)
	{
		if (path_check)
			ft_putstr_fd (ft_strjoin (command, ": no such file or directory\n"), \
			STDERR_FILENO);
		else
			ft_putstr_fd (ft_strjoin (command, ": command not found\n"), \
			STDERR_FILENO);
	}
	else if (status == 126)
		ft_putstr_fd (ft_strjoin (command, ":  Permission denied\n"), \
		STDERR_FILENO);
	exit (status);
}