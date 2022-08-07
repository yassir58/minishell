/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:58:44 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 19:10:41 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_valid_option(char *option)
{
	int	i;

	i = 0;
	if (option[i] == '-')
	{
		i++;
		while (option [i] && option[i] == 'n')
			i++;
		if (option[i] == 0)
			return (1);
	}
	return (0);
}

int	cd_error(int err, char *arg)
{
	if (!err)
		return (builtin_err (" : Not a directory\n", arg));
	else
		return (builtin_err (": No such file or directory\n", arg));
	return (0);
}

int	cd_prev_pwd(t_env_list *env_list)
{
	t_env_list	*tmp;
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

void	cd_to_home(t_env_list *env_list)
{
	t_env_list	*tmp;

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

int	cd_function(char *arg, t_env_list **env_list)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	if (arg == NULL)
		cd_to_home (*env_list);
	else if (!ft_strcmp (arg, "~"))
		cd_to_home (*env_list);
	else if (!ft_strcmp (arg, "-"))
		cd_prev_pwd (*env_list);
	else
	{
		err = chdir (arg);
		if (err == -1)
			err = is_dir (arg);
		if (err == -1 || err == 1)
			return (cd_error (err, arg));
	}
	update_pwd_env (env_list);
	return (err);
}
