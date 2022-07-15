#include "../includes/minishell.h"

env_list_t *get_env_list (char *env[])
{
    int i;
    env_list_t *head;

    i = 1;
    head = NULL;
    printf("%s:%s = %d\n", env[i], env[i + 1], ft_strcmp(env[i], env[i + 1]));
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

    node = malloc (sizeof (env_list_t));
    envTab = NULL;
    if (!node)
       return (NULL);
    envTab = ft_split (envStr, '=');
    node->variable_name = envTab[0];
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