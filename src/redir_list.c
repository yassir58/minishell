#include "../includes/minishell.h"

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