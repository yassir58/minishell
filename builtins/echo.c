#include "../includes/minishell.h"


int main (int argc, char *argv[])
{
    int i = 1;
    char thrilling;

    thrilling = '\0';
    if (strcmp (argv[i], "-n"))
        thrilling = '\n';
    else
        i++;

    while (argv[i])
    {
        if (i == (argc - 1))
            printf ("%s", argv[i]);
        else
            printf ("%s ", argv[i]);
        i++;
    }
    printf ("%c", thrilling);
    return (EXIT_SUCCESS);
}