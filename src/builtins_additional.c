/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:36:43 by ochoumou          #+#    #+#             */
/*   Updated: 2022/07/02 14:54:00 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int    ft_unset(t_exec_node *exec_node, env_list_t *list, shell_args_t *args)
{
    int i;
    int size;
    char **cmds;

    i = 1;
    cmds = get_commands(exec_node->cmd);
    size = number_of_el(cmds);
    args->exit_code = 0;
    while (i < size)
    {
        if (cmds[i] && !ft_isdigit(cmds[i][1]))
            delete_env_variable(cmds[i], list);
        else
        {
            printf("Minishell: unset: %s: not a valid identifier\n", cmds[i]);
            args->exit_code = 1;
            return (1);
        }
    }
    return (0);
}

int ft_env(t_exec_node *exec_node, env_list_t *list, shell_args_t *args)
{
    char **cmds;

    cmds = get_commands(exec_node->cmd);
    if (number_of_el(cmds) == 1)
    {
        print_env_list(list);
        args->exit_code = 0;
    }
    else
    {
        args->exit_code = 1;
        perror("Minishell: env: illegal option\n");
        return (1);
    }
    return (0);
}  

void handle_exit(char **cmds, shell_args_t *args)
{
    if (number_of_el(cmds) > 2)
    {
        perror("Minishell: exit: too many arguments\n");
        args->exit_code = 1;
    }
    else if (number_of_el(cmds) == 2) 
        args->exit_code = ft_atoi(cmds[1]);
}

int ft_exit(t_exec_node *exec_node, env_list_t *list, shell_args_t *args)
{
    char **cmds;

    cmds = get_commands(exec_node->cmd);    
    args->exit_code = 0;
    printf("exit\n");
    handle_exit(cmds, args);
    exit(args->exit_code);
    return (1);
}