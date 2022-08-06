/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:23:47 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 16:29:22 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_prev_pwd(env_list_t *env_list)
{
	env_list_t	*tmp;
	int			err;

	tmp = env_list;
	while (tmp)
	{
		if (!(strcmp (tmp->variable_name, "OLDPWD")))
			break ;
		tmp = tmp->next;
	}
	err = chdir (tmp->value);
	if (err == -1)
		return (builtin_err (" :no such file or directory\n", tmp->value));
	return (0);
}

void	cd_to_home(env_list_t *env_list)
{
	env_list_t	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (!(ft_strcmp (tmp->variable_name, "HOME")))
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		chdir (tmp->value);
	else
		ft_putstr_fd ("cd :HOME not set\n", 2);
}

char	*get_pwd_env(env_list_t *list)
{
	env_list_t	*tmp;
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

int	update_pwd_env(env_list_t **list)
{
	char		*current;
	char		*old;
	env_list_t	*tmp;

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

char	*get_pwd(env_list_t *env_list)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd (NULL, 0);
	if (!buffer)
		buffer = get_pwd_env (env_list);
	return (buffer);
}
