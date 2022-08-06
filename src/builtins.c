/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:25:44 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 17:27:01 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd_function(t_env_list *env_list)
{
	char	*pwd;

	pwd = get_pwd (env_list);
	printf ("%s\n", pwd);
	return (0);
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
			err = isDir (arg);
		if (err == -1 || err == 1)
			return (cd_error (err, arg));
	}
	update_pwd_env (env_list);
	return (err);
}

int	echo_function(t_shell_args *args, char *argv[], int argc)
{
	int		i ;
	char	thrilling;

	thrilling = '\n';
	i = 0;
	if (argc > 1)
	{
		if (check_for_valid_option (argv[i]) == 1)
		{
			while (argv[i] && (check_for_valid_option (argv[i]) == 1))
				i++;
			thrilling = '\0';
		}
		while (argv[i])
		{
			if (i == (argc - 1))
				echo_print (args, argv[i]);
			else
				printf ("%s ", argv[i]);
			i++;
		}
	}
	if (thrilling)
		printf ("%c", thrilling);
	return (0);
}

int	builtin_err(char *err, char *arg)
{
	char	*res;

	if (arg)
		res = ft_strjoin (arg, err);
	else
		res = err;
	ft_putstr_fd (res, 2);
	return (1);
}

void	echo_print(t_shell_args *args, char *str)
{
	t_env_list	*env;

	env = args->env_list;
	if (!ft_strcmp (str, "~"))
	{
		while (env)
		{
			if (!ft_strcmp (env->variable_name, "HOME"))
				printf ("%s", env->value);
			env = env->next;
		}
	}
	else
		printf ("%s", str);
}
