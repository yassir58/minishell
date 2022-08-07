/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:04:08 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/07 12:34:54 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset_error(void)
{
	ft_putstr_fd("Minishell: unset: not a valid identifier\n", 2);
	g_data->exit_code = 1;
	return (1);
}

int	ft_unset(t_exec_node *exec_node, t_env_list **list)
{
	int		i;
	int		size;
	char	**cmds;

	(void)list;
	i = 1;
	cmds = get_commands(exec_node->cmd->cmds);
	size = number_of_el(cmds);
	g_data->exit_code = 0;
	while (i < size)
	{
		if (validate_args(cmds[i], "_"))
		{
			if (!ft_strcmp(cmds[i], "PATH"))
				delete_env_variable(list, "SPATH");
			delete_env_variable(list, cmds[i]);
		}
		else
			ft_unset_error();
		i++;
	}
	free_string_table(cmds);
	return (0);
}
