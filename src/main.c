#include "../includes/minishell.h"




int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;

    init_signals();
    g_data = init_global ();
    args = init_args (env);
    rl_catch_signals = 0;
    (void)argc;
    (void)argv;
    while (1)
    {
        args->prompt = update_prompt (args);
        args->line = prompt(args->prompt);
        args->lexer_list = lexer (args, args->line);
        args->exec_node = parse (args, args->lexer_list);
        args->status = init_command (args);
        if (!args->status)
            get_children_status (&(args->status));
        g_data->exit_code = args->status;
    }
    /// free allocated global data
    return (0);
}
