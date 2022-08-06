/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:58:26 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 17:16:59 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redir_input(shell_args_t *args, t_redirect *redirect_node, int *err)
{
	int	fd;

	fd = access(redirect_node->filename, (F_OK));
	if (!ft_strcmp(redirect_node->filename, ""))
	{
		if (redirect_node->token == WORD)
			redir_err (redirect_node->filename, " :ambiguous redirect\n");
		else
			redir_err (redirect_node->filename, \
			" : No such file or directory\n");
		*err = 1;
		return (-1);
	}
	if (fd == -1)
	{
		redir_err (redirect_node->filename, " : No such file or directory \n");
		*err = 1;
		return (-1);
	}
	else
	{
		fd = access (redirect_node->filename, (R_OK));
		if (fd == -1)
		{
			redir_err (redirect_node->filename, " : Permission denied\n");
			*err = 1;
			return (-1);
		}
	}
	fd = open (redirect_node->filename, O_RDONLY, 0644);
	return (fd);
}

int	handle_redir_output(shell_args_t *args, t_redirect *redirect_node, int *err)
{
	int	fd;

	if (!ft_strcmp(redirect_node->filename, ""))
	{
		if (redirect_node->token == WORD)
			redir_err (redirect_node->filename, " :ambiguous redirect\n");
		else
			redir_err (redirect_node->filename, \
			" : No such file or directory\n");
		*err = 1;
		return (-1);
	}
	fd = access (redirect_node->filename, (F_OK));
	if (fd != -1)
	{
		fd = access (redirect_node->filename, (F_OK | W_OK));
		if (fd == -1)
		{
			redir_err (redirect_node->filename, " : Permission denied\n");
			*err = 1;
			return (-1);
		}
	}
	fd = open (redirect_node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	handle_redir_append(shell_args_t *args, t_redirect *redirect_node, int *err)
{
	int	fd;

	if (!ft_strcmp(redirect_node->filename, ""))
	{
		if (redirect_node->token == WORD)
			redir_err (redirect_node->filename, " :ambiguous redirect\n");
		else
			redir_err (redirect_node->filename, \
			" : No such file or directory\n");
		*err = 1;
		return (-1);
	}
	fd = access (redirect_node->filename, (F_OK));
	if (fd != -1)
	{
		fd = access (redirect_node->filename, (F_OK | W_OK));
		if (fd == -1)
		{
			redir_err (redirect_node->filename, " : Permission denied\n");
			*err = 1;
			return (-1);
		}
	}
	fd = open (redirect_node->filename, O_APPEND | O_CREAT | O_RDWR, 0644);
	return (fd);
}

int	trait_herdoc(shell_args_t *args, t_redirect *temp, int *in, int *fds)
{
	int	err;

	err = 0;
	pipe(fds);
	*in = fds[READ_END];
	err = write (fds[WRITE_END], temp->heredoc_content, \
	ft_strlen (temp->heredoc_content));
	close_fd (fds[WRITE_END]);
	if (err == -1)
		return (exit_with_failure (args, "failed to write to pipe\n"));
	return (err);
}

int	handle_redirections(shell_args_t *args, t_exec_node *exec_node, int *in, int *out)
{
	t_redirect	*temp;
	int			err;
	int			fds[2];
	int			status;

	temp = exec_node->cmd->redir_list;
	err = 0;
	status = 0;
	while (temp)
	{
		if (temp->type == REDIRIN)
			*in = handle_redir_input (args, temp, &status);
		else if (temp->type == REDIROUT)
			*out = handle_redir_output (args, temp, &status);
		else if (temp->type == APPEND)
			*out = handle_redir_append (args, temp, &status);
		else if (temp->type == HEREDOC)
			status = trait_herdoc (args, temp, in, fds);
		if (status)
			return (status);
		temp = temp->next;
	}
	return (status);
}
