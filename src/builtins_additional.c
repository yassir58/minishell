/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_additional.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:36:43 by ochoumou          #+#    #+#             */
/*   Updated: 2022/07/21 16:33:08 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int    ft_unset(t_exec_node *exec_node, env_list_t *list, shell_args_t *args)
// {
//     int i;
//     int size;
//     char **cmds;

//     i = 1;
//     cmds = get_commands(exec_node->cmd);
//     size = number_of_el(cmds);
//     args->exit_code = 0;
//     while (i < size)
//     {
//         if (cmds[i] && !ft_isdigit(cmds[i][1]))
//             delete_env_variable(cmds[i], list);
//         else
//         {
//             printf("Minishell: unset: %s: not a valid identifier\n", cmds[i]);
//             args->exit_code = 1;
//             return (1);
//         }
//     }
//     return (0);
// }

// int ft_env(t_exec_node *exec_node, env_list_t *list, shell_args_t *args)
// {
//     char **cmds;

//     cmds = get_commands(exec_node->cmd);
//     if (number_of_el(cmds) == 1)
//     {
//         print_unsorted_env(list);
//         args->exit_code = 0;
//     }
//     else
//     {
//         args->exit_code = 1;
//         perror("Minishell: env: illegal option\n");
//         return (1);
//     }
//     return (0);
// }  

// void handle_exit(char **cmds, shell_args_t *args)
// {
//     if (number_of_el(cmds) > 2)
//     {
//         perror("Minishell: exit: too many arguments\n");
//         args->exit_code = 1;
//         return ;
//     }
//     else if (!ft_isdigit(cmds[1][0]))
//     {
//         perror("Minishell: exit: numeric argument required\n");
//         args->exit_code = 2;
//     }
//     else if (number_of_el(cmds) == 2)
//         args->exit_code = ft_atoi(cmds[1]);
//     else if (number_of_el(cmds) == 2)
//     {
//         if (is_number(cmds[1]))
//             args->exit_code = ft_atoi(cmds[1]);
//         else
//             perror("Minishell: exit: numeric argument required\n");
//     }
//     exit(args->exit_code);
// }

// int ft_exit(t_exec_node *exec_node, env_list_t *list, shell_args_t *args)
// {
//     char **cmds;

//     cmds = get_commands(exec_node->cmd);
//     args->exit_code = 0;
//     printf("exit\n");
//     handle_exit(cmds, args);
//     return (1);
// }

// void    swap_nodes(env_list_t *a, env_list_t *b)
// {
//     char *key;
//     char *value;
//     int index;

//     key = a->variable_name;
//     value = a->value;
//     index = a->index;
//     a->variable_name = b->variable_name;
//     a->value = b->value;
//     a->index = b->index;
//     b->variable_name = key;
//     b->value = value;
//     b->index = index;
// }

// int env_list_size(env_list_t *list)
// {
//     env_list_t *tmp;
//     int i;

//     i = 0;
//     tmp = list;
//     while (tmp != NULL)
//     {
//         i += 1;
//         tmp = tmp->next;
//     }
//     return (i);
// }

// void    order_env_list(env_list_t *list)
// {
//     env_list_t *tmp_i;
//     env_list_t *tmp_j;
//     int         tmp;

//     tmp_i = list;
//     while (tmp_i != NULL)
//     {
//         tmp_j = tmp_i->next;
//         while (tmp_j != NULL)
//         {
//             if (ft_strcmp(tmp_i->variable_name, tmp_j->variable_name) > 0)
//                 swap_nodes(tmp_i, tmp_j);
//             tmp_j = tmp_j->next;
//         }
//         tmp_i = tmp_i->next;
//     }
// }

// void    print_unsorted_env(env_list_t *list)
// {
//     int i;
//     env_list_t *tmp;

//     i = 1;
//     tmp = list;
//     while (tmp != NULL)
//     {
//         while (tmp != NULL)
//         {
//             if (i == tmp->index)
//             {
//                 printf("%s=%s order: %d\n",tmp->variable_name, tmp->value, tmp->index);
//                 if (i == env_list_size(list))
//                     break;
//                 i += 1;
//             }
//             else
//                 tmp = tmp->next;
//         }
//         if (i != env_list_size(list))
//             tmp = list;
//         else
//         {
//             if (tmp)
//                 tmp = tmp->next;
//         }
//     }
// }

// int    validate_export_args(char **cmds)
// {
//     int i;

//     i = 1;
//     while (cmds[i])
//     {
//         if (ft_isalpha(cmds[i][0]))
//             i++;
//         else
//         {
//             perror("bash: export: not a valid identifier\n");
//             return (1);
//         }
//     }
//     return (0);
// }

// void    add_export_variable(char **cmds, env_list_t *list)
// {
//     int i;
    
//     i = 1;
//     while (cmds[i])
//     {
//         create_env_node(cmds[i],i);
//         i++;
//     }
// }

// void    ft_export(t_exec_node *exec_node, env_list_t *list, shell_args_t *args)
// {
//     char **cmds;
//     int i;

//     i = 0;
//     cmds = get_commands(exec_node->cmd->cmds);
//     // if there is no argument just print the list of env sorted.
//     if (!cmds[1])
//         print_env_list(list);
//     // validate that the arguments are valid.
//     // add the nodes entered into the linked list.
//     else if (number_of_el(cmds) > 1)
//     {
//         if(!validate_export_args(cmds))
//             add_export_variable(cmds, list);
//     }
// }