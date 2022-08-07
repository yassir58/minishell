/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:12:21 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 19:12:09 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_piped_commands(t_shell_args *args)
{
	t_exec_node		*tmp;
	t_exec_utils	*utils;
	int				status;

	status = 0;
	tmp = args->exec_node;
	utils = init_exec_utils ();
	utils->fds = open_fd_table (nodes_number(args), args);
	while (tmp)
	{
		utils->id = fork_child (args);
		if (!(utils->id))
		{
			status = handle_redirections (args, tmp, &(utils->infile),
					&(utils->outfile));
			if (status)
				return (status);
			exec_cmd (args, tmp, utils);
		}
		utils->indx++;
		tmp = tmp->next;
	}
	close_fd_table (utils->fds);
	free(utils);
	return (status);
}

void	link_pipes(t_exec_node *tmp, int **fds, int indx)
{
	if (tmp->prev != NULL && tmp->next != NULL)
		handle_doubly_piped (indx, fds);
	else if (tmp->next == NULL && tmp->prev != NULL)
		handle_last_command (indx, fds);
	else if (tmp->next != NULL && tmp->prev == NULL)
		handle_first_command (indx, fds);
}

int	builtin_routine(t_shell_args *args, t_exec_node *exec_node, int in, int out)
{
	char	**cmds;
	int		exit_status;

	cmds = get_commands (exec_node->cmd->cmds);
	exit_status = 0;
	if (!ft_strcmp (cmds[0], "cd"))
		exit_status = handle_cd (args, cmds);
	else if (!advanced_strcmp (cmds[0], "pwd"))
		pwd_function (args->env_list);
	else if (!advanced_strcmp (cmds[0], "echo"))
		echo_function (args, cmds, number_of_el (cmds));
	else if (!advanced_strcmp (cmds[0], "env"))
		ft_env (exec_node, args->env_list);
	else if (!advanced_strcmp (cmds[0], "unset"))
		ft_unset (exec_node, &args->env_list);
	else if (!advanced_strcmp (cmds[0], "exit"))
		ft_exit (exec_node);
	else if (!advanced_strcmp (cmds[0], "export"))
		ft_export(exec_node, args->env_list);
	free_tab (cmds);
	if (in != -1 && in != 0)
		close (in);
	if (out != -1 && out != 1)
		close (out);
	return (exit_status);
}

void	exec_command(t_shell_args *args, t_exec_node *exec_node)
{
	char	**cmds;
	char	**path;
	int		status;
	int		path_check;

	status = 0;
	path_check = 0 ;
	cmds = get_commands (exec_node->cmd->cmds);
	path = get_path (args, cmds, &status, &path_check);
	if (!path[0])
		shell_err (cmds[0], status, path_check);
	execve (path[0], cmds, get_env_table (args->env_list));
}

char	**check_for_path(char *cmd)
{
	char	**path_table;
	char	**cmd_path;
	int		i;

	path_table = NULL;
	cmd_path = NULL;
	i = 0;
	if (ft_strchr (cmd, '/'))
	{
		path_table = ft_split (cmd, '/');
		if (cmd[0] == '/' )
			cmd_path = handle_absolue_path (path_table);
		else
			cmd_path = handle_relative_path (path_table);
		free_tab (path_table);
	}
	return (cmd_path);
}
