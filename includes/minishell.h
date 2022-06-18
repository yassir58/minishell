#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

/// defining macros
#define OPERATOR 0
#define WORD 1
#define SINGLE_QUOTED_SEQUENCE 2
#define DOUBLE_QUOTED_SEQUENCE 3
#define VARIABLE 4
#define DELIMTERS "'\" "
#define OPERATORS ">|<"
#define TRUE 1
#define FALSE 0


typedef struct lexer_node_s
{
    int token;
    char *start;
    int length;
    int joinable;
    int closed;
    int invalid;
    struct lexer_node_s *next;
} lexer_node_t;


typedef struct env_list_s 
{
    char *variable_name;
    char *value;
    struct env_list_s *next;
} env_list_t;

lexer_node_t *lexer (char *line);
lexer_node_t *handle_regular (char *line, int *index);
lexer_node_t *handle_delim (char *line, int *index);
lexer_node_t *handle_operator (char *line, int *index);
void handle_quote (char *line, int *index, lexer_node_t **node);
void push_to_list (lexer_node_t **head, lexer_node_t *node);
void create_token_list (lexer_node_t **head, lexer_node_t *temp);
void free_list(lexer_node_t *node);
void print_token (int token);
void testing (lexer_node_t *node);
lexer_node_t *init_node ();
void syntax_error (lexer_node_t *node);
void syntax_validation (lexer_node_t *node);
void check_word (lexer_node_t *tokens_list);
lexer_node_t *expand_variables (lexer_node_t *tokens_list);
char *handle_variables (char *str);
char *extract_var_name (char *str, int *index);
char *get_variable_value (char *str, int *i);
char *push_char (char *str, char c);
void expand_single (lexer_node_t *head, lexer_node_t *temp);
env_list_t *get_env_list (char *env[]);
env_list_t *create_env_node (char *envStr);
void push_env_node (env_list_t **head, env_list_t *node);
void free_tab (char *tab[]);
void pwd_function (env_list_t *env_list);
void test_env_list (env_list_t *list);
int cd_function (char *arg, int flag, env_list_t **env_list);
void cd_to_home (env_list_t *env_list);
int check_for_dots (char *arg, env_list_t *list);
char *get_pwd_env (env_list_t *list);
int update_pwd_env (env_list_t **list);
char *get_pwd (env_list_t *env_list);
void echo_function (char *argv[], int argc);

#endif