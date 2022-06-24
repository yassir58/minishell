 #include "../includes/minishell.h"

/*
void print_token (int token)
{
    if (token == OPERATOR)
        printf ("OPERATOR \n");
    else if (token == WORD)
        printf ("WORD \n");
    else if (token == SINGLE_QUOTED_SEQUENCE)
        printf ("SINGLE_QUOTED_SEQUENCE \n");
    else
        printf ("DOUBLE_QUOTED_SEQUENCE \n");
}

void testing (lexer_node_t *node)
{
    printf (" __________________ lexer output __________________\n");
    if (!node)
        printf ("NULL ==> \n");
    else
    {
        print_token (node->token);
        printf ("%s \n", node->start);
        printf ("JOINABLE\n");
        //free (node);
    }
}


void test_env_list (env_list_t *list)
{
    env_list_t *tmp;
    env_list_t *ptr;


    tmp = list;
    while (tmp)
    {
        if (!strcmp (tmp->variable_name, "PWD") || !strcmp (tmp->variable_name, "OLDPWD"))
        {
            printf ("{name:%s}\n", tmp->variable_name);
            printf ("{value:%s}\n", tmp->value);
        }
        tmp = tmp->next;
    }
    tmp = list;
    while (tmp)
    {
        ptr = tmp;
        tmp = tmp->next;
        free (ptr);
    }
}

char *test_cd (lexer_node_t *node, env_list_t *list)
{
    char *buffer;
    buffer = NULL;
    if (node->next)
    {
        cd_function (node->next->start, 0, &list);
        buffer = getcwd (NULL, 0); 
    }
    else
    {
        cd_function (NULL, 0, &list);
        buffer = getcwd (NULL, 0); 
    }
    return (buffer);
}


*/
/// testing


int main (int argc, char *argv[])
{
    char *ping_path = "/bin/ls";
    char *grep_path = "/bin/echo";
    int fds[2];
    int id1;
    int id2;

    id1 = 0;
    id2 = 0;
    char *first_command[5]  = {"ls",  NULL};
    char *second_command[3] = {"echo", NULL};
    (void)argv;
    if (argc > 1)
    {
        if (!pipe (fds))
        {
            id1 = fork ();
            if (id1 == 0)
            {
                close (fds[0]);
                printf ("process : %d writes \n", getpid());
                dup2 (fds[1], STDOUT_FILENO);
                close (fds[1]);
                execve (ping_path, first_command, NULL);
                exit (EXIT_SUCCESS);
            }
            else
            {
                id2 = fork ();
                if (id2 == 0)
                {
                    dup2 (fds[0], STDIN_FILENO);
                    close (fds[0]);
                    close (fds[1]);
                    execve (grep_path, second_command, NULL);
                    exit (EXIT_SUCCESS);
                }
            }
        }
    }
    close (fds[0]);
    close (fds[1]);
    waitpid (id1,  NULL, 0);
    waitpid (id2,   NULL, 0);
    return (0);
}