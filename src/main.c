#include "../includes/minishell.h"

int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;
    char *buffer;
    int id;

    args = malloc (sizeof (shell_args_t));
    args->line = "";
    args->env = env;
    args->env_list = get_env_list (args->env);
    while (strcmp(args->line, "quit") != 0)
    {
        args->prompt = update_prompt (args);
        args->line = readline (args->prompt);
        args->lexer_list = lexer (args->line);
        check_word (args->lexer_list);
        syntax_validation (args->lexer_list);
        args->exec_node = parse (args->lexer_list);
        test_piped_commands (args);
        get_childer_status ();
        args->prompt = update_prompt (args);
        free (args->line);
    }
    return (0);
}