/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:52:17 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 16:53:32 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*allocation_err(void)
{
	write (2, "Allocation Error !\n", 19);
	return (NULL);
}

int	open_pipe(int *fd, shell_args_t *args)
{
	int	err;

	err = pipe (fd);
	if (err == -1)
		exit_with_failure (args, "pipe failed !\n");
	return (err);
}

int	close_fd(int fd)
{
	int	err;

	err = close (fd);
	if (err == -1)
		write (2, "failed to close fd !\n", 21);
	return (err);
}

int	exit_with_failure(shell_args_t *args, char *err_message)
{
	write (2, err_message, ft_strlen (err_message));
	free (g_data);
	free (args);
	exit (EXIT_FAILURE);
}

int	fork_child(shell_args_t *args)
{
	int	err;

	err = fork ();
	if (err == -1)
		exit_with_failure (args, "Failed to fork !");
	return (err);
}
