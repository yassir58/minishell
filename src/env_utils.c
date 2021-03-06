#include "../includes/minishell.h"

env_list_t *get_env_list (char *env[])
{
    int i;
    env_list_t *head;

    i = 0;
    head = NULL;
    while (env[i])
    {
        push_env_node (&head, create_env_node (env[i]));
        i++;
    }
    push_env_node (&head, create_path_node ());
    init_old_pwd (&head);
    return (head);
}

env_list_t *create_env_node (char *envStr)
{
    char **envTab;
    env_list_t *node;

    node = malloc (sizeof (env_list_t));
    envTab = NULL;
    if (!node)
       return (NULL);
    envTab = ft_split (envStr, '=');
    node->variable_name = envTab[0];
    node->value = envTab[1];
    node->next = NULL;
    return (node);
}

void push_env_node (env_list_t **head, env_list_t *node)
{
    env_list_t *head_pointer;

    head_pointer = *head;
    if (*head == NULL)
        *head = node;
    else
    {
        while (head_pointer->next)
            head_pointer = head_pointer->next;
        head_pointer->next = node;
    }
}

void free_tab (char *tab[])
{
    int i;

    i = 0;
    while (tab[i])
    {
        free (tab[i]);
        i++;
    }
    free (tab);
}

env_list_t *create_path_node (void)
{
    env_list_t *path_node;

    path_node = malloc (sizeof (env_list_t));
    if (!path_node)
        return (allocation_err ());
    path_node->variable_name = "SPATH";
    path_node->value = ft_strdup (_PATH_STDPATH);
    path_node->next = NULL;
    return (path_node);
}

void init_old_pwd (env_list_t **env_list)
{
    env_list_t *tmp;

    tmp = *env_list;
    while (tmp)
    {
        if (!ft_strcmp (tmp->variable_name, "OLDPWD"))
            tmp->value = ft_strdup ("");
        tmp= tmp->next;
    }
}