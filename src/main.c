#include "../includes/minishell.h"

int main (int argc ,char *argv[], char *env[])
{
    shell_args_t *args;
    char *buffer;

    args = malloc (sizeof (shell_args_t));
    args->env_list = get_env_list (env);
    args->prompt = ft_strjoin (get_pwd (args->env_list), "$");
    args->line = "";
    while (strcmp(args->line, "quit") != 0)
    {
        args->line = readline (args->prompt);
        args->lexer_list = lexer (args->line);
        check_word (args->lexer_list);
        args->exec_node = parse (args->lexer_list);
        builtin_routine (args);
        args->prompt = ft_strjoin (get_pwd (args->env_list), "$");
        printf ("pwd:%s\n", buffer);
        free (args->line);
    }
    return (0);
}