#include "../includes/minishell.h"
#include <stdio.h>

/** GRAMMAR
 *  <EXP> : <COMMAND>
 *  <COMMAND> : <EXP> | <COMMAND>
 * */
int check_node(lexer_node_t *node, char *operator)
{
    if (node->token == 0)
    {
        if (ft_strcmp(node->start, operator) == 0)
            return (1);
    }
    return (0);
}

int check_redirect(lexer_node_t *node)
{
    if (node->token == OPERATOR)
    {
        if (!check_node(node, "|"))
            return (1);
    }
    return (0);
}

int redirect_type(lexer_node_t *node)
{
    if (node->token == OPERATOR)
    {
        if (check_node(node, "<"))
            return (REDIRIN);
        else if (check_node(node, ">"))
            return (REDIROUT);
        else if (check_node(node, ">>"))
            return (APPEND);
        else if (check_node(node, "<<"))
            return (HEREDOC);
    }
    return (0);
}
/** @Function:    Arguments_number
 *  @Description: The function bellow will help me find how many spots i should allcate for
 *  the arguments.
 * */

void    print_commands(t_cmd *list)
{
    t_cmd *tmp;

    tmp = list;
    printf("Commands\n");
    while (tmp != NULL)
    {
        printf("Command args: %s\n", tmp->cmd);
        tmp = tmp->next;
    }
}

void    print_redirects(t_redirect *list)
{
    t_redirect *tmp;

    tmp = list;
    printf("Redirections:\n");
    while (tmp != NULL)
    {
        printf("Redirect file: %s Type: %d Redirect Content: %s\n", tmp->filename, tmp->type, tmp->heredoc_content);
        tmp = tmp->next;
    }
}

void    handle_heredoc(t_redirect *node)
{
    char *input;

    input = readline("heredoc>");
    while (input != NULL)
    {
        if (ft_strcmp(input, node->filename))
        {
            node->heredoc_content = ft_strjoin(node->heredoc_content, input);
            node->heredoc_content = ft_strjoin(node->heredoc_content, "\n");
        }
        else
            break;
        input = readline("heredoc>");
    }
}

void    handle_command(lexer_node_t *node)
{
    t_redirect *redirects;
    t_cmd *cmds;
    t_redirect *tmp;
    int i;

    cmds = NULL;
    tmp = NULL;
    redirects = NULL;
    i = 0;
    while (node != NULL && !check_node(node, "|"))
    {
        while (node && node->token == 1)
        {
            add_command(&cmds, new_command(ft_strdup(node->start)));
            node = node->next;
        }
        if (node && check_redirect(node))
        {
            tmp = add_redirect(&redirects, new_redirect(ft_strdup(node->next->start), NULL ,redirect_type(node)));
            if (redirect_type(node) == HEREDOC)
                handle_heredoc(tmp);
            node = node->next;
        }
        node = node->next;
    }
    print_commands(cmds);
    print_redirects(redirects);
}

// t_ast_node *new_pipe_node(t_ast_node *left, t_ast_node *right)
// {
//     t_ast_node *node;

//     node = (t_ast_node *)malloc(sizeof(t_ast_node));
//     if (!node)
//         return (NULL);
//     node->type = PIPE_NODE;
//     node->value->PIPE.left = left;
//     node->value->PIPE.right = right;
//     return (node);
// }

// t_ast_node *new_cmd_node(t_cmd_node *cmd, t_redirect *redir)
// {
//     t_ast_node *node;

//     node = (t_ast_node *)malloc(sizeof(t_ast_node));
//     if (!node)
//         return (NULL);
//     node->type = CMD_NODE;
//     node->value->CMD.cmds = cmd;
//     node->value->CMD.redir_list = redir;
//     return (node);
// }

// t_ast_node *parse_command(lexer_node_t *node)
// {
//     t_cmd *cmds;
//     t_redirect *redirects;
//     t_ast_node *ast_cmd;

//     cmds = NULL;
//     redirects = NULL;
//     if (node)
//         return ;
//     handle_command(node, cmds, redirects);
//     ast_cmd = new_cmd_node(cmds, redirects);
//     if (!ast_cmd)
//         return (NULL);
//     return ast_cmd;
// }

// Todo List:
// Handle CMD: DONE
// Handle PIPE
// Hanlde REDIR: DONE

t_redirect *new_redirect(char *name, char *heredoc, t_redir_type type)
{
    t_redirect *node;

    node = (t_redirect *)malloc(sizeof(t_redirect));
    if (!node)
        return (NULL);
    node->type = type;
    node->filename = name;
    node->heredoc_content = heredoc;
    node->next = NULL;
    return (node);
}


// This function will be modified to return the address of the new node.
t_redirect  *add_redirect(t_redirect **list, t_redirect *node)
{
    if (!*list)
    {
        *list = node;
        return (node);
    }
    node->next = *list;
    *list = node;
    return (node);
}

/** Note: This should be the first function since am 
 * sure that the first word is gonna be always a command.
 */

t_cmd *new_command(char *cmd)
{
    t_cmd *node;

    node = (t_cmd *)malloc(sizeof(t_cmd));
    if(!node)
        return (NULL);
    node->cmd = cmd;
    node->next = NULL;
    return (node);
}

void    add_command(t_cmd **list, t_cmd *cmd)
{
    if (!*list)
    {
        *list = cmd;
        return ;
    }
    cmd->next = *list;
    *list = cmd;
}



// void    print_table(char **table)
// {
//     int i;
    
//     i = 0;
//     while (table[i])
//     {
//         printf("%s\n", table[i]);
//         i++;
//     }
// }


// t_redirect *handle_redirect(lexer_node_t *token)
// {
//     t_redirect *redir;
//     if (check_redirect(token))
//     {
//     }
//     else
//         return (NULL);
// }