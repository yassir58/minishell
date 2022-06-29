#include "../includes/minishell.h"

int main (int argc ,char *argv[], char *env[])
{
    char *line;
    lexer_node_t *tmp;
    lexer_node_t *node;
    // env_list_t *list;
    char *buffer;


    line = "";
    buffer = NULL;
    buffer = getcwd (NULL, 0);
    // list = get_env_list (env);
    while (1)
    {
        line = prompt();
        // printf ("_________________________ parser output analysis _________________________\n");
        node = lexer (line);
        check_word (node);
        tmp = node;
        // testing (node);
        parse(tmp);
        // while (tmp)
        // {
        //     testing (tmp);
        //     tmp = tmp->next ;
        // }
        free (line);
    }
    return (0);
}