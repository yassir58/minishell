#ifndef MINISHELL_H
#define MINI_SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


int validate_args ();
char **get_command ();
char *get_input (char *line, int *ptr);
int arg_count (char *line);
void free_tab (char **tab);

#endif