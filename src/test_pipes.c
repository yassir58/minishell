#include "../includes/minishell.h"




int main (void)
{
    char *cmd1[3] = {"cat", "README.md", NULL};
    char *cmd2[3] = {"grep", "lexer", NULL };
    t_test_node *node1;
    t_test_node *node2;
    int fds[2];
    int id = 0;
    node1 = malloc (sizeof (t_test_node));
    node2 = malloc (sizeof (t_test_node));
    node1->command = cmd1;
    node1->next = node2;
    node2->command = cmd2;
    node2->next =NULL;
    if (pipe (fds) == -1)
    {
        return (2);
    }
        node1->write_end = fds[1];
        node2->read_end = fds[0];
        id = fork ();
        if (!id)
        {
            close(node2->read_end);
            dup2 (node1->write_end , 1);
            close (node1->write_end);
            execv ("/bin/cat", node1->command);
        }
        else
        {
            id = fork ();
            if (!id)
            {
                close(node1->write_end);
                dup2 (node2->read_end, 0);
                close(node2->read_end);
                execv ("/usr/bin/grep", node2->command);
            }
        }
    close(fds[1]);
    close(fds[0]);
    while (waitpid (-1, NULL, 0) != -1);
    return (0);
}