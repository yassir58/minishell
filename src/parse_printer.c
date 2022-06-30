#include "../includes/minishell.h"

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

