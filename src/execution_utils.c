/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:12:32 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 15:06:22 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_first_command(int indx, int **fds_table)
{
	close_fd (fds_table[indx][READ_END]);
	close_unused_fds (fds_table, indx);
	dup2 (fds_table[indx][WRITE_END], STDOUT_FILENO);
	close_fd (fds_table[indx][WRITE_END]);
}

void	handle_last_command(int indx, int **fds_table)
{
	close_fd (fds_table[indx - 1][WRITE_END]);
	close_unused_fds (fds_table, indx - 1);
	dup2 (fds_table[indx - 1][READ_END], STDIN_FILENO);
	close_fd (fds_table[indx - 1][READ_END]);
}

void	handle_doubly_piped(int indx, int **fds_table)
{
	close_unused_fds_2 (fds_table, indx - 1, indx);
	close_fd (fds_table[indx - 1][WRITE_END]);
	close_fd (fds_table[indx][READ_END]);
	dup2 (fds_table[indx - 1][READ_END], STDIN_FILENO);
	dup2 (fds_table[indx][WRITE_END], STDOUT_FILENO);
	close_fd (fds_table[indx - 1][READ_END]);
	close_fd (fds_table[indx][WRITE_END]);
}

int	nodes_number(shell_args_t *args)
{
	t_exec_node	*tmp;
	int			len;

	len = 0;
	tmp = args->exec_node;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	get_children_status(void)
{
	int	flag;
	int	status;

	flag = 0;
	while (flag != -1)
	{
		flag = waitpid (-1, &status, 0);
		if (WIFEXITED(status) && flag != -1)
			g_data->exit_code = WEXITSTATUS (status);
		else if (WIFSIGNALED (status) && flag != -1)
		{
			if (WTERMSIG(status) + 128 == 131)
			{
				g_data->exit_code = 131;
				printf ("Quit : 3\n");
			}
		}
	}
}
