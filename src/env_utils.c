#include "../includes/minishell.h"

t_env_list *get_env_list (char *env[])
{
    int i;
    t_env_list *head;

    i = 0;
    head = NULL;
    if (env)
    {
        if (number_of_el (env) == 0)
            init_env_list (&head);
        else
        {
            while (env[i] && ft_strlen(env[i]) > 0)
            {
                push_env_node (&head, create_env_node (env[i], i));
                i++;
            }
        }
        push_env_node (&head, create_path_node ());
    }
    init_old_pwd (&head);
    return (head);
}


t_env_list *create_env_node (char *envStr, int index)
{
    char **envTab;
    t_env_list *node;
    int shell;

    node = malloc (sizeof (t_env_list));
    envTab = NULL;
    if (!node)
       return (NULL);
    envTab = ft_split (envStr, '=');
    node->variable_name = envTab[0];
    if (!ft_strcmp(node->variable_name, "SHLVL"))
    {
        shell = ft_atoi(envTab[1]) + 1;
        free(envTab[1]);
        node->value = ft_itoa(shell);
    }
    else
        node->value = envTab[1];
    node->index = index;
    node->next = NULL;
    free(envTab);
    return (node);
}

void push_env_node (t_env_list **head, t_env_list *node)
{
    t_env_list *head_pointer;

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

t_env_list *create_path_node (void)
{
    t_env_list *path_node;

    path_node = malloc (sizeof (t_env_list));
    if (!path_node)
        return (allocation_err ());
    path_node->variable_name = "SPATH";
    path_node->value = ft_strdup (_PATH_STDPATH);
    path_node->next = NULL;
    return (path_node);
}

void init_old_pwd (t_env_list **env_list)
{
    t_env_list *tmp;

    tmp = *env_list;
    while (tmp)
    {
        if (!ft_strcmp (tmp->variable_name, "OLDPWD"))
        {
            free(tmp->value);
            tmp->value = ft_strdup ("");
        }
        tmp= tmp->next;
    }
}