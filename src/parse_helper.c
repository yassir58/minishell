#include "../includes/minishell.h"
#include <stdio.h>

int check_node(lexer_node_t *node, char *operator)
{
    if (node && node->token == 0)
    {
        if (ft_strcmp(node->start, operator) == 0)
            return (1);
    }
    return (0);
}

int check_redirect(lexer_node_t *node)
{
    if (node && node->token == OPERATOR)
    {
        if (!check_node(node, "|"))
            return (1);
    }
    return (0);
}

int redirect_type(lexer_node_t *node)
{
    if (node && node->token == OPERATOR)
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
    return (-1);
}

void    print_commands(t_cmd *list)
{
    t_cmd *tmp;
    int i;

    tmp = list;
    i = 0;
    printf("Commands:\n");
    while (tmp != NULL)
    {
        printf("args[%d]: %s\n", i,tmp->cmd);
        tmp = tmp->next;
        i++;
    }
}

void    print_redirects(t_redirect *list)
{
    t_redirect *tmp;

    tmp = list;
    printf("Redirections:\n");
    while (tmp != NULL)
    {
        printf("Files: \n");
        display(tmp->filenames);
        if (tmp->type == APPEND)
            printf("Type: Append ");
        else if (tmp->type == HEREDOC)
            printf("Type: Heredoc ");
        else if (tmp->type == REDIRIN)
            printf("Type: Redir Input ");
        else if (tmp->type == REDIROUT)
            printf("Type: Redir Output ");
        if (tmp->heredoc_content)
            printf("Redirect Content: %s\n", tmp->heredoc_content);
        else
            printf("\n");
        tmp = tmp->next;
    }
}

void    print_one_node(t_exec_node *node)
{
        printf("===================================\n");
        printf("CMD NODE\n");
        if (node->builtin)
            printf("BUILTIN\n");
        else if (node->piped)
            printf("PIPED\n");
        print_commands(node->cmd->cmds);
        if (node->cmd->redir_list)
            print_redirects(node->cmd->redir_list);
}

void    print_exec_node(t_exec_node *list)
{
    t_exec_node *tmp;

    tmp = list;
    while (tmp != NULL)
    {
        printf("===================================\n");
        if (tmp->builtin)
            printf("BUILTIN\n");
        if (tmp->piped)
            printf("PIPED\n");
        print_commands(tmp->cmd->cmds);
        // display(get_commands(tmp->cmd->cmds));
        if (tmp->cmd->redir_list)
            print_redirects(tmp->cmd->redir_list);
        tmp = tmp->next;
    }
}

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

int     count_filenames(lexer_node_t *node)
{
    int i;

    i = 0;
    while (node && node->token != OPERATOR)
    {
        i += 1;
        node = node->next;
    }
    return (i);
}

char   **filenames_table(lexer_node_t **node, int files)
{
    int i;
    char **filenames;

    i = 0;
    filenames = (char **)malloc(sizeof(char *) * (files + 1));
    if (!filenames)
        return (NULL);
    if (files == 1)
    {
        filenames[i++] = ft_strdup((*node)->next->start);
        (*node) = (*node)->next->next;
    }
    else 
    {
        while (i < files)
        {
            filenames[i++] = ft_strdup((*node)->start);
            (*node) = (*node)->next;
        }
    }
    filenames[i] = NULL;
    return (filenames);
}

// void    handle_redirect_input(lexer_node_t **node, t_redirect *redirects)
// {

// }

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

bool is_builtin(t_cmd_node *cmd)
{
    char *arg;

    // These are the tests for the get_command function.
    // printf("Arguments:\n");
    // display(get_commands(cmd->cmds));
    arg = cmd->cmds->cmd;
    if (!advanced_strcmp(arg, B1) || !advanced_strcmp(arg, B2) || !advanced_strcmp(arg, B3) \
    || !advanced_strcmp(arg, B4) || !advanced_strcmp(arg, B5) ||!advanced_strcmp(arg, B6) || !advanced_strcmp(arg, B7))
        return (true);
    return (false);
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
   print_exec_node(list);
   return (list);
}

// t_exec_node *new_exec_pipe()
// {
//     t_exec_node *node;

//     node = (t_exec_node *)malloc(sizeof(t_exec_node));
//     if (!node)
//         return (NULL);
//     node->type = PIPE_NODE;
//     node->cmd = NULL;
//     node->builtin = FALSE;
//     node->piped = FALSE;
//     node->next = NULL;
//     node->prev = NULL;
//     return (node);
// }

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

t_redirect *new_redirect(char **names, char *heredoc, t_redir_type type)
{
    t_redirect *node;
    int i;

    i = 0;
    node = (t_redirect *)malloc(sizeof(t_redirect));
    if (!node)
        return (NULL);
    node->type = type;
    node->filenames = names;
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

int commands_number(t_cmd *list)
{
    t_cmd   *tmp;
    int     i;

    i = 0;
    tmp = list;
    if (!list)
        return (0);
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

char    **get_commands(t_cmd *cmds)
{
    t_cmd *tmp;
    int i;
    char **commands;

    i = 0;
    tmp = cmds;
    commands = (char **)malloc(sizeof(char *) * (commands_number(cmds) + 1));
    if (!commands)
        return (NULL);
    while (tmp)
    {
        commands[i++] = ft_strdup(tmp->cmd);
        tmp = tmp->next;
    }
    commands[i] = NULL;
    return (commands);
}

int number_of_el(char **cmds)
{
    int i;

    i = 0;
    while (cmds[i] != NULL)
        i++;
    return (i);
}

void    display(char **cmds)
{
    int i;
    int number;

    i = 0;
    number = number_of_el(cmds);
    while (i < number)
    {
        printf("File[%d]: %s\n",i,cmds[i]);
        i++;
    }
}