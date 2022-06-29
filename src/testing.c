#include "../includes/minishell.h"


void print_token (int token)
{
    if (token == OPERATOR)
        printf ("OPERATOR \n");
    else if (token == WORD)
        printf ("WORD \n");
    else if (token == SINGLE_QUOTED_SEQUENCE)
        printf ("SINGLE_QUOTED_SEQUENCE \n");
    else
        printf ("DOUBLE_QUOTED_SEQUENCE \n");
}

void testing (lexer_node_t *node)
{
    printf (" __________________ lexer output __________________\n");
    if (!node)
        printf ("NULL ==> \n");
    else
    {
        print_token (node->token);
        printf ("%s \n", node->start);
        printf ("JOINABLE\n");
        //free (node);
    }
}

void test_env_list (env_list_t *list)
{
    env_list_t *tmp;
    env_list_t *ptr;


    tmp = list;
    while (tmp)
    {
        if (!strcmp (tmp->variable_name, "PWD") || !strcmp (tmp->variable_name, "OLDPWD"))
        {
            printf ("{name:%s}\n", tmp->variable_name);
            printf ("{value:%s}\n", tmp->value);
        }
        tmp = tmp->next;
    }
    tmp = list;
    while (tmp)
    {
        ptr = tmp;
        tmp = tmp->next;
        free (ptr);
    }
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
        printf("File: %s ", tmp->filename);
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
    if (node->type == CMD_NODE)
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
    else
    {
        printf("===================================\n");
        printf("PIPE NODE\n");
    }
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
        if (tmp->cmd->redir_list)
            print_redirects(tmp->cmd->redir_list);
        tmp = tmp->next;
    }
}

void test_exec_node (t_exec_node *node)
{
    t_exec_node *tmp;
    char **tab;

    tmp = node;
    printf ("<__________ testing exec node ________> \n");
    while (tmp)
    {
        tab = get_commands (tmp->cmd->cmds);
        display (tab);
        free_tab (tab);
        tmp = tmp->next;
    }
}


char *update_prompt (shell_args_t *args)
{
    char *pwd;
    char **tab;
    char *res;
    char *elm;

    elm = ":\033[0;31m$ \033[0m";
    res = NULL;
    pwd= get_pwd (args->env_list);
    if (pwd && ft_strcmp (pwd, "/"))
    {
        tab = ft_split (pwd, '/');
        res = tab[number_of_el(tab) - 1];
        res = ft_strjoin (res, elm);
        free_tab (tab);
        return (res);
    }
    else
        return (ft_strjoin(pwd, elm));
}

void print_fd_table (shell_args_t *args)
{
    int i;

    i = 0;
    while (args->fds_table[i])
    {
       
        printf ("[ %d : %d ]\n", args->fds_table[i][0], args->fds_table[i][1]);    
        i++;
    }
}