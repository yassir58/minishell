#include "../includes/minishell.h"

int main (int argc ,char *argv[], char *env[])
{
    char *line;
    lexer_node_t *tmp;
    lexer_node_t *node;
    env_list_t *list;
    char *prompt;
    char *buffer;


    line = "";
    buffer = NULL;
    buffer = getcwd (NULL, 0);
    list = get_env_list (env);
    while (strcmp(line, "quit") != 0)
    {
        prompt = ft_strjoin (buffer, "$>");
        line = readline (prompt);
        if (line && strcmp (line, ""))
        {
            node = lexer (line);
            check_word (node);
            // node = expand_variables (node);
            syntax_validation (node);
            if (!strcmp(node->start, "cd"))
                test_cd (node, list);
            else if (!strcmp (node->start, "env"))
                test_env_list (list);
            else
            {
                printf ("_________________________ command lexical analysis _________________________\n");
                tmp = node;
                while (tmp)
                {
                    testing (tmp);
                    tmp = tmp->next ;
                }
            }
            free (line);
        }
    }
    return (0);
}