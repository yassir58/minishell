#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef struct lexer_node
{
    char *content;
    int length;
} LEXER;

enum TOKENS {
    STRING = 0,
    D_QUOTE = '"',
    S_QUOTE = '\'',
    SPACE = ' ',
    ENV_VAR = '$',
    REDIRECT = '>',
    INPUTRED = '<',
    APPEND = '>>',
    HEREDOC = '<<'
};

enum  // This should indicate which state the token are in
{
    DEFAULT = 0,
    DOUBLE_Q = 1,
    SINGLE_Q = 2
};

#endif