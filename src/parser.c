/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:57 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/04 19:04:56 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void    get_file_content(t_redirect *tmp)
{
    int fd;
    char *content;

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

int handle_ctrl(shell_args_t *args, t_redirect *tmp, lexer_node_t *word)
{
    int pid;
    int fd;
    
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


void    handle_heredoc(shell_args_t *args, t_redirect *node, int fd, lexer_node_t *word)
{
    char *input;
    char *output;
    
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
            break;
        write(1, "> ", 2);
        input = advanced_get_next_line(0, 0);
    }
    write(fd, output, ft_strlen(output));
    exit(0);
}

void    parse_cmd_args(t_cmd **cmds, lexer_node_t **node)
{
    while (*node && ((*node)->token == WORD || (*node)->token == DOUBLE_QUOTED_SEQUENCE || (*node)->token == SINGLE_QUOTED_SEQUENCE))
    {
        add_command(cmds, new_command(ft_strdup((*node)->start)));
        (*node) = (*node)->next;
    }
}

t_exec_node *check_piped(lexer_node_t **node, t_cmd *cmds, t_redirect *redirects)
{
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

t_exec_node *parse_command(shell_args_t *args, lexer_node_t **node)
{
    t_redirect *redirects;
    t_redirect *tmp;
    t_cmd *cmds;

    cmds = NULL;
    tmp = NULL;
    redirects = NULL;
    while ((*node != NULL) && !check_node(*node, "|"))
    {
        parse_cmd_args(&cmds, node);
        if ((*node) && check_redirect((*node)))
        {
            tmp = add_redirect(&redirects, new_redirect(ft_strdup((*node)->next->start), NULL ,redirect_type((*node)), (*node)->next->token));
            if (redirect_type((*node)) == HEREDOC)
            {
                if(!handle_ctrl(args ,tmp, (*node)))
                    return (new_exec_cmd(command_node(redirects, cmds), TRUE, TRUE));
            }
            (*node) = (*node)->next->next;
        }
    }
    return (check_piped(node, cmds, redirects));
}

t_exec_node   *parse(shell_args_t *args, lexer_node_t *node)
{
   t_exec_node *list;
   t_exec_node *exec_node;
   t_exec_node *last_node;
   lexer_node_t *token;

   token = node;
   list = NULL;
   if (!syntax_validation (args))
    {
        if (token && !check_node(node, "|"))
        {
            while (token)
            {
                exec_node = parse_command(args, &token);
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
    }
    return (list);
}
