#include "../includes/minishell.h"


int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;
    char *buffer;
    int id;
    int status;
    int g_status = 0;

    init_signals();
    args = malloc (sizeof (shell_args_t));
    args->line = NULL;
    args->env = env;
    args->env_list = get_env_list (args->env);
    while (strcmp(args->line, "quit") != 0)
    {
        args->prompt = update_prompt (args);
        args->line = readline (args->prompt);
        args->lexer_list = lexer (args->line);
        args->exec_node = parse (args, args->lexer_list);
        print_exec_node (args->exec_node);
        status = init_command (args);
        if (status)
            printf ("status : %d\n", status);
        else
        {
            g_status = get_childer_status ();
            printf ("g_status %d \n", g_status);
        }
        args->prompt = update_prompt (args);
        free (args->line);
    }
    return (0);
}
