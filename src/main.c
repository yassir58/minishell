/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 11:13:30 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/07 11:52:44 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Don't forget the Makefile does not compile libft

int	main(int argc, char *argv[], char *env[])
{
	t_shell_args	*args;

	init_signals();
	g_data = init_global ();
	args = init_args (env);
	rl_catch_signals = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		args->prompt = update_prompt (args);
		args->line = prompt(args->prompt);
		args->lexer_list = lexer (args, args->line);
		args->exec_node = parse (args, args->lexer_list);
		init_command (args);
		get_children_status ();
		free_lexer(&args->lexer_list);
		free_parser(&args->exec_node);
		free(args->prompt);
		free(args->line);
	}
	free(args);
	free(g_data);
	return (0);
}
