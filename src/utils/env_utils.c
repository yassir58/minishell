/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:12:48 by yelatman          #+#    #+#             */
/*   Updated: 2022/08/06 19:27:16 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*get_env_list(char *env[])
{
	int			i;
	t_env_list	*head;

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

t_env_list	*create_env_node(char *envStr, int index)
{
	char		**env_tab;
	t_env_list	*node;
	int			shell;

	node = malloc (sizeof (t_env_list));
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

void	push_env_node(t_env_list **head, t_env_list *node)
{
	t_env_list	*head_pointer;

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

t_env_list	*create_path_node(void)
{
	t_env_list	*path_node;

	path_node = malloc (sizeof (t_env_list));
	if (!path_node)
		return (allocation_err ());
	path_node->variable_name = "SPATH";
	path_node->value = ft_strdup (_PATH_STDPATH);
	path_node->next = NULL;
	return (path_node);
}
