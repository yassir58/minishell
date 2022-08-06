/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelatman <yelatman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:12:48 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 16:51:34 by yelatman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

env_list_t	*get_env_list(char *env[])
{
	int			i;
	env_list_t	*head;

	i = 0;
	head = NULL;
	if (env)
	{
		if (number_of_el (env) == 0)
			init_env_list (&head);
		else
		{
			while (env[i] && ft_strlen(env[i]) > 0)
			{
				push_env_node (&head, create_env_node (env[i], i));
				i++;
			}
		}
		push_env_node (&head, create_path_node ());
	}
	init_old_pwd (&head);
	return (head);
}

env_list_t	*create_env_node(char *envStr, int index)
{
	char		**env_tab;
	env_list_t	*node;
	int			shell;

	node = malloc (sizeof (env_list_t));
	env_tab = NULL;
	if (!node)
		return (NULL);
	env_tab = ft_split (envStr, '=');
	node->variable_name = env_tab[0];
	if (!ft_strcmp(node->variable_name, "SHLVL"))
	{
		shell = ft_atoi(env_tab[1]) + 1;
		free(env_tab[1]);
		node->value = ft_itoa(shell);
	}
	else
		node->value = env_tab[1];
	node->index = index;
	node->next = NULL;
	free(env_tab);
	return (node);
}

void	push_env_node(env_list_t **head, env_list_t *node)
{
	env_list_t	*head_pointer;

	head_pointer = *head;
	if (*head == NULL)
		*head = node;
	else
	{
		while (head_pointer->next)
			head_pointer = head_pointer->next;
		head_pointer->next = node;
	}
}

env_list_t	*create_path_node(void)
{
	env_list_t	*path_node;

	path_node = malloc (sizeof (env_list_t));
	if (!path_node)
		return (allocation_err ());
	path_node->variable_name = "SPATH";
	path_node->value = ft_strdup (_PATH_STDPATH);
	path_node->next = NULL;
	return (path_node);
}

void	init_old_pwd(env_list_t **env_list)
{
	env_list_t	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (!ft_strcmp (tmp->variable_name, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup ("");
		}
		tmp = tmp->next ;
	}
}
