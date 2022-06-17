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
            list = get_env_list (env);
            if (!strcmp(node->start, "cd"))
            {
                if (node->next)
                {
                    printf ("%s\n", node->next->start);
                    cd_function (node->next->start, 0, list);
                    buffer = getcwd (NULL, 0); 
                }
                else
                {
                    cd_function (NULL, 0, get_env_list (env));
                    buffer = getcwd (NULL, 0); 
                }
            }
            else if (!strcmp (node->start, "env"))
            {
                test_env_list (list);
                printf ("realPwd:%s\n", buffer);
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