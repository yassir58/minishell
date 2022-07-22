#include "../includes/minishell.h"


int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;
    char *buffer;

    init_signals();
    args = malloc (sizeof (shell_args_t));
    args->env_list = get_env_list (env);
    args->line = NULL;
    heredoc_status = 0;
    while (1)
    {
        args->prompt = update_prompt (args);
        args->line = prompt(args->prompt);
        args->lexer_list = lexer (args->line);
        check_word (args->lexer_list);
        syntax_validation (args->lexer_list);
        args->exec_node = parse (args->lexer_list);
        // execution_function (args);
        args->prompt = update_prompt (args);
        // test_env_list(args->env_list);
        free (args->line);
    }
    return (0);
}
