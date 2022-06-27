#include "../includes/minishell.h"

void    handle_heredoc(t_redirect *node)
{
    char *input;

    input = readline("heredoc>");
    while (input != NULL)
    {
        if (ft_strcmp(input, node->filenames[0]))
        {
            node->heredoc_content = ft_strjoin(node->heredoc_content, input);
            node->heredoc_content = ft_strjoin(node->heredoc_content, "\n");
        }
        else
            break;
        input = readline("heredoc>");
    }
}

t_exec_node *parse_command(lexer_node_t **node)
{
    t_redirect *redirects;
    t_redirect *tmp;
    t_cmd *cmds;
    int i;

    i = 0;
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
            if ((*node) && redirect_type((*node)) == REDIRIN)
            {
                (*node) = (*node)->next;
                tmp = add_redirect(&redirects, new_redirect(filenames_table(node, count_filenames((*node))), NULL , REDIRIN));
            }
            else
                tmp = add_redirect(&redirects, new_redirect(filenames_table(node, 1), NULL ,redirect_type((*node))));
            if ((*node) && redirect_type((*node)) == HEREDOC)
                handle_heredoc(tmp);
        }
    }
    if (cmds && (*node))
    {
        if (check_node(*node, "|"))
        {
            (*node) = (*node)->next;
            return (new_exec_cmd(command_node(redirects, cmds), TRUE));
        }
    }
    return (new_exec_cmd(command_node(redirects, cmds), FALSE));
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
   return (list);
}