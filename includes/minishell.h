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

// >> <<
typedef struct lexer_node_s
{
    int token;
    char *start;
    int length;
    int joinable;
    int closed;
    int invalid;
    void *next;
} lexer_node_t;

typedef enum s_node_type
{
    CMD_NODE,
    PIPE_NODE
} t_node_type;

typedef enum s_redir_type 
{
    REDIRIN,
    REDIROUT,
    APPEND,
    HEREDOC
} t_redir_type;

typedef struct s_ast_node 
{
    t_node_type type;
    t_node_value *value; // This will point on the type of node and will set the type of that node
    struct S_AST_NODE *next;
} t_ast_node;

typedef struct s_pipe_node 
{
    t_ast_node *left;
    t_ast_node *right;
} t_pipe_node;

typedef struct s_redirect 
{
    t_redir_type type;
    char *filename;
    struct s_redirect *next;
} t_redirect;

typedef struct s_cmd_node 
{
    char **cmd; // This table will contain the command and expanded variables and options
    t_redirect *redir_list;
} t_cmd_node;

typedef union s_node_value
{
    t_pipe_node PIPE;
    t_cmd_node CMD;
} t_node_value;

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

#endif