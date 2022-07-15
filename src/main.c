#include "../includes/minishell.h"



int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;
    char *buffer;

    init_signals();
    args = malloc (sizeof (shell_args_t));
    args->env_list = get_env_list (argv);
    test_env_list(args->env_list);
    ft_order_list(args->env_list);
    test_env_list(args->env_list);
    args->line = NULL;
    // while (1)
    // {
    //     args->prompt = update_prompt (args);
    //     args->line = prompt(args->prompt);
    //     args->lexer_list = lexer (args->line);
    //     check_word (args->lexer_list);
    //     syntax_validation (args->lexer_list);
    //     args->exec_node = parse (args->lexer_list);
    //     // execution_function (args);
    //     args->prompt = update_prompt (args);
    //     test_env_list(args->env_list);
    //     free (args->line);
    // }
    return (0);
}