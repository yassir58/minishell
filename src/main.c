#include "../includes/minishell.h"
#define MAX_SIZE 1000

int main (int argc ,char *argv[], char *env[])
{
    char *line;
    lexer_node_t *tmp;
    lexer_node_t *node;
    char buffer[MAX_SIZE];
    char *prompt;


    line = "";
    getcwd (buffer, sizeof (buffer)); 
    while (strcmp(line, "quit") != 0)
    {
        prompt = ft_strjoin (buffer, "$>");
        line = readline (prompt);
        // printf ("_________________________ command lexical analysis _________________________\n");
        if (line && strcmp (line, ""))
        {
            node = lexer (line);
            check_word (node);
            node = expand_variables (node);
            if (!strcmp(node->start, "cd"))
            {
                if (node->next)
                {
                    printf ("%s\n", node->next->start);
                    cd_function (node->next->start, 0, get_env_list (env));
                    getcwd (buffer, sizeof (buffer)); 
                }
                else
                {
                    cd_function (NULL, 0, get_env_list (env));
                    getcwd (buffer, sizeof (buffer)); 
                }
            }
            // tmp = node;
            // while (tmp)
            // {
            //     testing (tmp);
            //     tmp = tmp->next ;
            // }
            free (line);
        }
    }
    return (0);
}