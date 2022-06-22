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
    printf("Commands:\n");
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

t_exec_node *parse_command(lexer_node_t *node)
{
    t_redirect *redirects;
    t_cmd *cmds;
    t_redirect *tmp;
    int i;

    i = 0;
    cmds = NULL;
    tmp = NULL;
    redirects = NULL;
    while (node != NULL && !check_node(node, "|"))
    {
        while (node && (node->token == WORD || node->token == DOUBLE_QUOTED_SEQUENCE || node->token == SINGLE_QUOTED_SEQUENCE))
        {
            add_command(&cmds, new_command(ft_strdup(node->start)));
            node = node->next;
        }
        if (node && check_redirect(node))
        {
            tmp = add_redirect(&redirects, new_redirect(ft_strdup(node->next->start), NULL ,redirect_type(node)));
            if (redirect_type(node) == HEREDOC)
                handle_heredoc(tmp);
            node = node->next->next;
        }
    }
    if (check_node(node, "|"))
        return (new_exec_node(CMD_NODE, command_node(redirects, cmds), TRUE));
    return (new_exec_node(CMD_NODE, command_node(redirects, cmds), FALSE));
}

bool command_type(t_cmd_node *cmd)
{
    if (cmd->cmds->cmd)
}

void    parse(lexer_node_t *node)
{
    // Handling the command
    printf("%d\n", node->token);

    // In case of pipe creating a new pipe command that will point on the next command
}

t_exec_node *new_exec_node(t_node_type type, t_cmd_node *cmd, bool piped)
{
    t_exec_node *node;

    node = (t_exec_node *)malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);
    if (type == CMD_NODE)
    {
        node->type = CMD_NODE;
        node->cmd = cmd;
        node->builting = command_type(cmd);
        node->piped = piped;
        node->next = NULL;
        node->prev = NULL; // The should be reseted.
    }
    else 
    {
        node->type = PIPE_NODE;
        node->piped = FALSE;
        node->builting = FALSE;
        node->cmd = NULL;
        node->next = NULL;
        node->prev = NULL; // This should be reseted.
    }
    return (node);
}

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

t_cmd_node *command_node(t_redirect *redirlist, t_cmd *cmdlist)
{
    t_cmd_node *node;

    node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
    if (!node)
        return (NULL);
    node->cmds = cmdlist;
    node->redir_list = redirlist;
    return (node);
}

t_redirect  *add_redirect(t_redirect **list, t_redirect *node)
{
    t_redirect *last;

    if (!*list)
    {
        *list = node;
        return (node);
    }
    last = last_redirect(*list);
    last->next = node;
    return (node);
}

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
    t_cmd *lst_node;

    if (!*list)
    {
        *list = cmd;
        return ;
    }
    lst_node = last_command(*list);
    lst_node->next = cmd;
}

t_redirect *last_redirect(t_redirect *lst)
{
    t_redirect *tmp;

    tmp = lst;
    if (!lst)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}

t_cmd *last_command(t_cmd *lst)
{
    t_cmd *tmp;

    tmp = lst;
    if (!lst)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}
