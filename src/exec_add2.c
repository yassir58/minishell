/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_add2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 14:44:34 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 17:27:01 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_cd(t_shell_args *args, char **cmds)
{
	int	exit_status ;

	exit_status = 0;
	if (number_of_el (cmds) >= 2)
		exit_status = cd_function (cmds[1], &args->env_list);
	else
		exit_status = cd_function (NULL, &args->env_list);
	return (exit_status);
}

void	link_rediriction_pipes(int infile, int outfile)
{
	if (infile > 0)
		dup2 (infile, STDIN_FILENO);
	if (outfile > 1)
		dup2 (outfile, STDOUT_FILENO);
}

int	handle_one_builtin_cmd(t_shell_args *args, int in, int out)
{
	int	status;
	int	id;

	status = 0;
	id = 0;
	if (!ft_strcmp (args->exec_node->cmd->cmds->cmd, "cd"))
		status = handle_cd (args, get_commands(args->exec_node->cmd->cmds));
	else if (!ft_strcmp (args->exec_node->cmd->cmds->cmd, "exit"))
		status = ft_exit (args->exec_node);
	else if (!ft_strcmp (args->exec_node->cmd->cmds->cmd, "export"))
		status = ft_export (args->exec_node, args->env_list);
	else if (!ft_strcmp (args->exec_node->cmd->cmds->cmd, "unset"))
		status = ft_unset (args->exec_node, &args->env_list);
	else
	{
		id = fork_child (args);
		if (!id)
			run_builtin (args, &in, &out);
	}
	return (status);
}

void	exec_cmd(t_shell_args *args, t_exec_node *tmp, t_exec_utils *utils)
{
	int	status;

	status = 0;
	link_pipes (tmp, utils->fds, utils->indx);
	link_rediriction_pipes (utils->infile, utils->outfile);
	if (tmp->builtin)
	{
		status = builtin_routine (args, tmp, utils->infile, utils->outfile);
		exit (status);
	}
	else
		exec_command (args, tmp);
}

void	run_builtin(t_shell_args *args, int *in, int *out)
{
	int	status;

	status = 0;
	status = handle_redirections (args, args->exec_node, in, out);
	if (status)
		exit (status);
	link_rediriction_pipes (*in, *out);
	status = builtin_routine (args, args->exec_node, *in, *out);
	exit (status);
}
