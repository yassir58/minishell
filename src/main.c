#include "../includes/minishell.h"


int main (int argc ,char *argv[])
{
    char *line;
    lexer_node_t *tmp;
    lexer_node_t *node;

    line = "";
    while (strcmp(line, "quit") != 0)
    {
        line = readline (">");
        printf ("_________________________ command lexical analysis _________________________\n");
        node = lexer (line);
        tmp = node;
        syntax_validation (node);
        while (tmp)
        {
            testing (tmp);
            tmp = tmp->next ;
        }
        free (line);
    }
    free_list (node);
    return (0);
}