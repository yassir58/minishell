#include "../includes/minishell.h"


int main (int argc ,char *argv[])
{
    char *line;
    lexer_node_t *tmp;
    lexer_node_t *node;

    line = "";
    while (strcmp(line, "quit") != 0)
    {
        line = readline ("@minishell: ");
        printf ("_________________________ parser output analysis _________________________\n");
        node = lexer (line);
        check_word (node);
        node = expand_variables (node);
        tmp = node;
        parse_command(tmp);
        // while (tmp)
        // {
        //     testing (tmp);
        //     tmp = tmp->next ;
        // }
        free (line);
    }
    return (0);
}