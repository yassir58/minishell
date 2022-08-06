/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 17:17:03 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 17:18:12 by yelatman         ###   ########.fr       */
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
