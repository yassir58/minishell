#include "../includes/minishell.h"

int main (int argc ,char *argv[], char *env[])
{
    char *line;
    lexer_node_t *tmp;
    lexer_node_t *node;
    // env_list_t *list;
    char *prompt;
    char *buffer;


    line = "";
    buffer = NULL;
    buffer = getcwd (NULL, 0);
    // list = get_env_list (env);
    while (strcmp(line, "quit") != 0)
    {
        line = readline ("@minishell: ");
        // printf ("_________________________ parser output analysis _________________________\n");
        node = lexer (line);
        check_word (node);
        // node = expand_variables (node);
        tmp = node;
        handle_command(tmp);
        // while (tmp)
        // {
        //     testing (tmp);
        //     tmp = tmp->next ;
        // }
        free (line);
    }
    return (0);
}