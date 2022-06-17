#include "../includes/minishell.h"

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
    printf("Print Commands\n");
    while (tmp != NULL)
    {
        printf("%s\n", tmp->cmd);
        tmp = tmp->next;
    }
}

void    print_redirects(t_redirect *list)
{
    t_redirect *tmp;

    tmp = list;
    printf("Print Redirect:\n");
    while (tmp != NULL)
    {
        printf("%s %d\n", tmp->filename, tmp->type);
        tmp = tmp->next;
    }
}

void    parse_command(lexer_node_t *node)
{
    int     i;
    t_cmd   *cmds;
    t_redirect *redirects;


    cmds = NULL;
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
            add_redirect(&redirects, new_redirect(ft_strdup(node->next->start),redirect_type(node)));
            node = node->next;
        }
    }
    print_commands(cmds);
    print_redirects(redirects);
}

// void    parse_main(lexer_node_t *node)
// {
//     t_cmd *cmds;
//     t_redirect *redirects;
    
//     cmds = NULL;
//     redirects = NULL;
//     if (node)
//         return ;
    
// }

// Todo List:
// Handle CMD: DONE
// Handle PIPE
// Hanlde REDIR: DONE

t_redirect *new_redirect(char *name, t_redir_type type)
{
    t_redirect *node;

    node = (t_redirect *)malloc(sizeof(t_redirect));
    if (!node)
        return (NULL);
    node->type = type;
    node->filename = name;
    node->next = NULL;
    return (node);
}

void    add_redirect(t_redirect **list, t_redirect *node)
{
    if (!*list)
    {
        *list = node;
        return ;
    }
    node->next = *list;
    *list = node;
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

// t_ast_node *create_node(t_node_type type, t_cmd *cmd, t_redirect *redirlist)
// {
//     t_ast_node *tree_node;
//     tree_node = (t_ast_node *)malloc(sizeof(t_ast_node));
//     if (!tree_node)
//         return (NULL);
//     if (type == CMD_NODE)
//     {
//         tree_node->type = CMD_NODE;
//         tree_node->value->CMD.redir_list = redirlist;
//     }
//     return (tree_node);
// }

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