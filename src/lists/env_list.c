/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:04 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 19:12:09 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export_list(t_env_list *list)
{
	t_env_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->variable_name, "SPATH"))
			printf("declare -x %s=\"%s\"\n", tmp->variable_name, tmp->value);
		tmp = tmp->next;
	}
}

void	print_env_list(t_env_list *list)
{
	t_env_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strcmp(tmp->variable_name, "SPATH"))
			printf("%s=\"%s\"\n", tmp->variable_name, tmp->value);
		tmp = tmp->next;
	}
}

void	delete_env_variable(t_env_list **list, char *key)
{
	t_env_list	*tmp;
	t_env_list	*prev;

	tmp = *list;
	if (tmp != NULL && (ft_strcmp(tmp->variable_name, key) == 0))
	{
		*list = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp != NULL && (ft_strcmp(tmp->variable_name, key) != 0))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp);
}

t_env_list	*search_env_variable(char *var, t_env_list *list)
{
	t_env_list	*node;

	node = list;
	while (node != NULL)
	{
		if (ft_strcmp(node->variable_name, var) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	init_old_pwd(t_env_list **env_list)
{
	t_env_list	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (!ft_strcmp (tmp->variable_name, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup ("");
		}
		tmp = tmp->next;
	}
}
