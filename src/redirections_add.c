/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:17:03 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 17:58:56 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_err(char *filename, char *err_message)
{
	char	*err;

	err = ft_strjoin (filename, err_message);
	ft_putstr_fd (err, 2);
}

int	is_dir(char *filename)
{
	struct stat	sfile;
	int			accs;

	accs = access (filename, (F_OK));
	if (accs == -1)
		return (-1);
	stat("filename", &sfile);
	if (S_ISREG(sfile.st_mode) == 0)
		accs = 1;
	return (accs);
}

int	check_amb_redirect(t_redirect *redirect_node, int *err)
{
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
	return (0);
}
