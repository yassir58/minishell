/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 15:04:03 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/07 13:03:14 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	order_env_list(t_env_list *list)
{
	t_env_list	*tmp_i;
	t_env_list	*tmp_j;

	tmp_i = list;
	while (tmp_i != NULL)
	{
		tmp_j = tmp_i->next;
		while (tmp_j != NULL)
		{
			if (ft_strcmp(tmp_i->variable_name, tmp_j->variable_name) > 0)
				swap_nodes(tmp_i, tmp_j);
			tmp_j = tmp_j->next;
		}
		tmp_i = tmp_i->next;
	}
}

int	check_valid_input(char **str)
{
	if (!str[1])
	{
		free_string_table(str);
		return (1);
	}
	free_string_table(str);
	return (0);
}

int	check_existing_variable(char *argument, t_env_list *list)
{
	t_env_list	*node;
	char		**object;

	object = ft_split(argument, '=');
	if (object[0])
	{
		node = search_env_variable(object[0], list);
		if (node)
		{
			if (!object[1])
			{
				free_string_table(object);
				return (-1);
			}
			free(node->value);
			node->value = object[1];
			free(object[0]);
			free(object);
			return (1);
		}
		else
			return (check_valid_input(object));
	}
	free_string_table(object);
	return (0);
}

void	add_export_variable(char **cmds, t_env_list *list)
{
	int	i;
	int	tmp;

	i = 1;
	tmp = 0;
	while (cmds[i])
	{
		tmp = check_existing_variable(cmds[i], list);
		if (tmp != -1 && tmp != 1)
			push_env_node (&list, create_env_node (cmds[i], i));
		i++;
	}
}

int	ft_export(t_exec_node *exec_node, t_env_list *list)
{
	char	**cmds;	
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	cmds = get_commands(exec_node->cmd->cmds);
	order_env_list(list);
	if (!cmds[1])
		print_export_list(list);
	else if (number_of_el(cmds) > 1)
	{
		ret = validate_export_args(cmds);
		if (!ret)
			add_export_variable(cmds, list);
		else
			return (ret);
	}
	free_string_table(cmds);
	return (0);
}
