#include "../includes/minishell.h"


int main (int argc ,char *argv[])
{
    char *line;
    lexer_node_t *node;
    lexer_node_t *tmp;

    line = "";
    while (strcmp(line, "quit") != 0)
    {
        line = readline (">");
        node = lexer (line);
        tmp = node;
        printf (" __________________ lexer output __________________\n");
        while (tmp)
        {
            write (1, tmp->start, tmp->length);
            write (1, "\n", 1);
            print_token (tmp->token);
            tmp = tmp->next;
        }
        free_list (node);
        free (line);
    }
    return (0);
}