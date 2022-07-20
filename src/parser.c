/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:57 by ochoumou          #+#    #+#             */
/*   Updated: 2022/07/20 22:25:20 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// We should be aware that in the case of ctrl c the minishell should not complete its job. we should add a condition
// That will stop that from happening

void    handle_heredoc(t_redirect *node, lexer_node_t *wp, int fd)
{
    char *input;

    write(1, ">", 1);
    input = advanced_get_next_line(0, 0);
    if (input == NULL)
        exit(1);
    while (input != NULL)
    {
        if (ft_strcmp(input, node->filename))
        {
            node->heredoc_content = ft_strjoin(node->heredoc_content, input);
            node->heredoc_content = ft_strjoin(node->heredoc_content, "\n");
        }
        else
            break;
        write(1, ">", 1);
        input = advanced_get_next_line(0, 0);
    }
    write(fd, node->heredoc_content, ft_strlen(node->heredoc_content));
    exit(0);
}

t_exec_node *parse_command(lexer_node_t **node)
{
    t_redir_type type;
    t_redirect *redirects;
    t_redirect *tmp;
    t_cmd *cmds;

    cmds = NULL;
    tmp = NULL;
    redirects = NULL;
    while ((*node != NULL) && !check_node(*node, "|"))
    {
        while (*node && ((*node)->token == WORD || (*node)->token == DOUBLE_QUOTED_SEQUENCE || (*node)->token == SINGLE_QUOTED_SEQUENCE))
        {
            add_command(&cmds, new_command(ft_strdup((*node)->start)));
            (*node) = (*node)->next;
        }
        if ((*node) && check_redirect((*node)))
        {
            tmp = add_redirect(&redirects, new_redirect(ft_strdup((*node)->next->start), NULL ,redirect_type((*node))));
            if (redirect_type((*node)) == HEREDOC)
            {
                int pid;
                int fd;
                int status;
                
                fd = open("/tmp/.minishell", O_CREAT | O_RDWR | O_TRUNC, 0644);
                pid = fork();
                if (pid == 0)
                    handle_heredoc(tmp, (*node), fd);
                else
                {
                    heredoc_status = pid;
                    wait(NULL);
                }
                if (heredoc_status)
                {
                    char *content;
                    fd = open("/tmp/.minishell", O_RDWR);
                    content = advanced_get_next_line(fd, 1);
                    while (content != NULL)
                    {
                        tmp->heredoc_content = ft_strjoin(tmp->heredoc_content, content);
                        free(content);
                        content = advanced_get_next_line(fd, 1);
                    }
                }
                else
                    return (new_exec_cmd(command_node(redirects, cmds), TRUE, TRUE));
            }
            (*node) = (*node)->next->next;
        }
    }
    if (cmds && (*node))
    {
        if (check_node(*node, "|"))
        {
            (*node) = (*node)->next;
            return (new_exec_cmd(command_node(redirects, cmds), TRUE, FALSE));
        }
    }
    if ((*node) && check_node(*node, "|"))
        (*node) = (*node)->next;
    return (new_exec_cmd(command_node(redirects, cmds), FALSE, FALSE));
}

t_exec_node   *parse(lexer_node_t *node)
{
   t_exec_node *list;
   t_exec_node *exec_node;
   t_exec_node *last_node;
   lexer_node_t *token;

   token = node;
   list = NULL;
   if (token && !check_node(node, "|"))
   {
       while (token)
       {
            exec_node = parse_command(&token);
            if (exec_node->status)
                break;
            if (!list)
            {
                exec_node->prev = NULL;
                list = exec_node;
            }
            else 
            {
                last_node = last_exec_node(list);
                last_node->next = exec_node;
                exec_node->prev = last_node;
            }
       }
   }
   print_exec_node(list);
   return (list);
}