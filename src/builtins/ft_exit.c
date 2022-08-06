/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:04:00 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 15:05:44 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_exit(char **cmds)
{
	if (number_of_el(cmds) > 2)
	{
		g_data->exit_code = 1;
		ft_putstr_fd("Minishell: exit: too many arguments\n", 2);
		return ;
	}
	else if (number_of_el(cmds) == 2)
	{
		if (is_number(cmds[1]))
		{
			g_data->exit_code = ft_atoi(cmds[1]);
			exit(g_data->exit_code);
		}
		else
		{
			g_data->exit_code = 255;
			printf("Minishell: exit: numeric argument required\n");
		}
	}
	exit(g_data->exit_code);
}

int	ft_exit(t_exec_node *exec_node)
{
	char	**cmds;

	cmds = get_commands(exec_node->cmd->cmds);
	g_data->exit_code = 0;
	printf("exit\n");
	handle_exit(cmds);
	return (g_data->exit_code);
}
