#include "../includes/minishell.h"

env_list_t *get_env_list (char *env[])
{
    int i;
    env_list_t *head;

    i = 1;
    head = NULL;
    while (env[i])
    {
        push_env_node (&head, create_env_node (env[i], i));
        i++;
    }
    return (head);
}

env_list_t *create_env_node (char *envStr, int index)
{
    char **envTab;
    env_list_t *node;
    int shell;

    node = malloc (sizeof (env_list_t));
    envTab = NULL;
    if (!node)
       return (NULL);
    envTab = ft_split (envStr, '=');
    node->variable_name = envTab[0];
    if (!ft_strcmp(node->variable_name, "SHLVL"))
    {
        shell = ft_atoi(envTab[1]) + 1;
        node->value = ft_itoa(shell);
    } 
    else
        node->value = envTab[1];
    node->index = index;
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