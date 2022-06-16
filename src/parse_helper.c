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
        else
            return (0);
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
/** @Function:    Arguments_number
 *  @Description: The function bellow will help me find how many spots i should allcate for
 *  the arguments.
 * */

int arguments_number(lexer_node_t *node)
{
    int i;

    i = 0;
    while (node != NULL && node->token != OPERATOR)
    {
        i += 1;
        node = node->next;
    }
    node = node->next;
    printf("%d\b ")
    if (node && node->token == OPERATOR && (check_redirect(node) == 0))
    {
        printf("Condition has been matched\n");
        node = node->next;
        if (node->next)
        {
            node = node->next;
            while (node != NULL && node->token != OPERATOR)
            {
                i += 1;
                node = node->next;
            }
        }
    }
    return (i);
}

// Todo List:
// Handle CMD
// Handle PIPE
// Hanlde REDIR



t_redirect *add_redirect_node(t_redirect *list, char *name, t_redir_type type)
{
    t_redirect *node;

    node = (t_redirect *)malloc(sizeof(t_redirect));
    if (!node)
        return (NULL);
    node->type = type;
    node->filename = name;
    node->next = list;
    return (node);
}

// t_redirect *handle_redirect(lexer_node_t *token)
// {
//     t_redirect *redir;
//     if (check_redirect(token))
//     {
//     }
//     else
//         return (NULL);
// }

/** Note: This should be the first function since am 
 * sure that the first word is gonna be always a command.
 */

char **parse_command(lexer_node_t *node)
{
    char **cmds;
    int i;

    i = 0;
    cmds = (char **)malloc(sizeof(char *) * (arguments_number(node) + 1));
    if (!cmds)
        return (NULL);
    while (node != NULL && node->token != 0)
    {
        cmds[i++] = node->start;
        node = node->next;
    }
    cmds[i] = NULL;
    return (cmds);
}

void    print_table(char **table)
{
    int i;
    
    i = 0;
    while (table[i])
    {
        printf("%s\n", table[i]);
        i++;
    }
}

t_ast_node *create_node(t_node_type type, char **cmd, t_redirect *redirlist)
{
    t_ast_node *tree_node;

    tree_node = (t_ast_node *)malloc(sizeof(t_ast_node));
    if (!tree_node)
        return (NULL);
    if (type == CMD_NODE)
    {
        tree_node->type = CMD_NODE;
        tree_node->value->CMD.cmd = cmd;
        tree_node->value->CMD.redir_list = redirlist;
    }
    return (tree_node);
}
