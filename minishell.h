#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"


int validate_args ();
char **get_command (int *count);
char *get_input (char *line, int *ptr);
int arg_count (char *line);
void free_tab (char **tab);
char *handle_quote (char *line, int *indx);
int input_validation (char **args, int count);
void increment_counters (int *len , int *i);
int exec_command ();
int get_quote_count (char delim, char *str, int indx);
#endif