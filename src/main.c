#include "../includes/minishell.h"


int main (int argc ,char *argv[])
{
    char *line;

    line = "";
    while (strcmp(line, "quit") != 0)
    {
        line = readline (">");
        lexer (line);
        free (line);
    }
    return (0);
}