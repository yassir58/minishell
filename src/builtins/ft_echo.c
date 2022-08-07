/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 18:59:46 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 19:27:56 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	echo_function(t_shell_args *args, char *argv[], int argc)
{
	int		i ;
	char	thrilling;

	thrilling = '\n';
	i = 1;
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
