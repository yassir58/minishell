/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:03:56 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 15:05:15 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_exec_node *exec_node, t_env_list *list)
{
	char	**cmds;

	cmds = get_commands(exec_node->cmd->cmds);
	if (number_of_el(cmds) == 1)
	{
		print_env_list(list);
		g_data->exit_code = 0;
	}
	else
	{
		g_data->exit_code = 1;
		ft_putstr_fd("Minishell: env: illegal option\n", 2);
		return (1);
	}
	return (0);
}
