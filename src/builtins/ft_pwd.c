/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:57:15 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 18:59:08 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_pwd_env(t_env_list *list)
{
	t_env_list	*tmp;
	char		*pwd;

	tmp = list;
	pwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp (tmp->variable_name, "PWD"))
			pwd = ft_strdup (tmp->value);
		tmp = tmp->next;
	}
	return (pwd);
}

int	update_pwd_env(t_env_list **list)
{
	char		*current;
	char		*old;
	t_env_list	*tmp;

	tmp = *list;
	current = getcwd (NULL, 0);
	if (!current)
		return (-1);
	old = get_pwd_env (*list);
	while (tmp)
	{
		if (!ft_strcmp (tmp->variable_name, "PWD"))
			tmp->value = current;
		else if (!ft_strcmp (tmp->variable_name, "OLDPWD"))
			tmp->value = old;
		tmp = tmp->next;
	}
	return (0);
}

char	*get_pwd(t_env_list *env_list)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd (NULL, 0);
	if (!buffer)
		buffer = get_pwd_env (env_list);
	return (buffer);
}

int	pwd_function(t_env_list *env_list)
{
	char	*pwd;

	pwd = get_pwd (env_list);
	printf ("%s\n", pwd);
	return (0);
}
