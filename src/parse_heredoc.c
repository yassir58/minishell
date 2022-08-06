/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 16:49:30 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 16:49:48 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_file_content(t_redirect *tmp)
{
	int		fd;
	char	*content;

	fd = open("/tmp/.minishell", O_RDWR);
	content = advanced_get_next_line(fd, 1);
	tmp->heredoc_content = ft_strdup("");
	while (content != NULL)
	{
		tmp->heredoc_content = free_joined(tmp->heredoc_content);
		tmp->heredoc_content = ft_strjoin(tmp->heredoc_content, content);
		free(content);
		content = advanced_get_next_line(fd, 1);
	}
}

int	handle_ctrl(t_shell_args *args, t_redirect *tmp, t_lexer_node *word)
{
	int	pid;
	int	fd;

	fd = open("/tmp/.minishell", O_CREAT | O_RDWR | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		handle_heredoc(args, tmp, fd, word);
	else
	{
		g_data->heredoc_status = pid;
		wait(NULL);
	}
	if (g_data->heredoc_status)
		get_file_content(tmp);
	else
		return (0);
	return (1);
}

void	handle_heredoc(t_shell_args *args, t_redirect *node, int fd, \
t_lexer_node *word)
{
	char	*input;
	char	*output;

	write(1, "> ", 2);
	input = advanced_get_next_line(0, 0);
	output = ft_strdup("");
	if (input == NULL)
		exit(1);
	while (input != NULL)
	{
		if (ft_strcmp(input, node->filename))
		{
			if (word->next->token == WORD)
				input = expand_variable(args, input);
			output = free_joined(output);
			output = ft_strjoin(output, input);
			output = ft_strjoin(output, "\n");
		}
		else
			break ;
		write(1, "> ", 2);
		input = advanced_get_next_line(0, 0);
	}
	write(fd, output, ft_strlen(output));
	exit(0);
}
