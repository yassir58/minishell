#include "../includes/minishell.h"

int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;
    char *buffer;

    args = malloc (sizeof (shell_args_t));
    args->env_list = get_env_list (env);
    args->line = "";
    while (strcmp(args->line, "quit") != 0)
    {
        args->prompt = update_prompt (args);
        args->line = readline (args->prompt);
        if (ft_strcmp (args->line, ""))
        {
            args->lexer_list = lexer (args->line);
            check_word (args->lexer_list);
            syntax_validation (args->lexer_list);
            args->exec_node = parse (args->lexer_list);
            //execution_function (args);
            args->prompt = update_prompt (args);
            free (args->line);
        }
    }
    return (0);
}