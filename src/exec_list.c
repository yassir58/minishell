#include "../includes/minishell.h"

t_exec_node *new_exec_cmd(t_cmd_node *cmd, bool piped)
{
    t_exec_node *node;

    node = (t_exec_node *)malloc(sizeof(t_exec_node));
    if (!node)
        return (NULL);
    node->type = CMD_NODE;
    node->cmd = cmd;
    if (node->cmd->cmds)
        node->builtin = is_builtin(cmd);
    else
        node->builtin = NULL;
    node->piped = piped;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}

t_exec_node *last_exec_node(t_exec_node *list)
{
    t_exec_node *tmp;

    tmp = list;
    if (!list)
        return (NULL);
    while (tmp->next != NULL)
        tmp = tmp->next;
    return (tmp);
}