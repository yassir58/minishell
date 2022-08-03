#include "../includes/minishell.h"


int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;

    init_signals();
    g_data = init_global ();
    args = init_args (env);
    // rl_catch_signals = 0;
    (void)argc;
    (void)argv;
    while (1)
    {
        args->prompt = update_prompt (args);
        args->line = prompt(args->prompt);
        args->lexer_list = lexer (args, args->line);
        args->exec_node = parse (args, args->lexer_list);
        init_command (args);
        get_children_status ();
        free_lexer(&args->lexer_list);
        free_parser(&args->exec_node);
        free(args->prompt);
        free(args->line);
    }
    /// free allocated global data
    return (0);
}
