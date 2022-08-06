/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:12:35 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 15:10:40 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_command(shell_args_t *args)
{
	int	status;

	status = 0;
	if (args->exec_node == NULL)
		g_data->exit_code = (unsigned char) 258;
	else if (args->exec_node && args->exec_node->next == NULL)
	status = handle_simple_command (args);
	else
		status = exec_piped_commands (args);
	g_data->exit_code = (unsigned char) status;
}

int	get_status(int pid)
{
	int	status;

	waitpid (pid, &status, 0);
	if (WIFEXITED(status))
		printf ("exit status %d\n", WEXITSTATUS(status));
	return (status);
}

char	**get_path(shell_args_t *args, char **cmds, int *status, int *pstatus)
{
	char	*path;
	char	**path_check;
	char	**path_table;
	char	*cmd;

	path_check = NULL;
	path_table = malloc (sizeof (char *) * 3);
	if (!path_table)
		allocation_err ();
	path_check = check_for_path (cmds[0]);
	path = NULL;
	path_table[2] = NULL;
	cmd = cmds[0];
	if (path_check)
	{
		path = path_check[0];
		path_table[1] = path_check[1];
		cmd = path_table[1];
		*pstatus = 1;
	}
	else
		path_table[1] = cmds[0];
	path = check_access (args, cmds[0], path, status);
	path_table[0] = path;
	return (path_table);
}
