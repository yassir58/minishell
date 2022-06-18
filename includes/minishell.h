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

typedef struct s_pipe_node 
{
    struct s_ast_node *left;
    struct s_ast_node *right;
} t_pipe_node;

typedef struct s_redirect 
{
    t_redir_type type;
    char *filename;
    char *heredoc_content;
    struct s_redirect *next;
} t_redirect;

typedef struct s_cmd {
    char *cmd;
    struct s_cmd *next;
} t_cmd;

typedef struct s_cmd_node 
{
    t_cmd *cmds;
    t_redirect *redir_list;
} t_cmd_node;

typedef union s_node_value
{
    t_pipe_node PIPE;
    t_cmd_node CMD;
} t_node_value;

typedef struct s_ast_node 
{
    t_node_type type;
    t_node_value *value;
} t_ast_node;


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

/* ======================= Parser Functions ========================== **/

void        print_commands(t_cmd *list);
t_ast_node  *parse_command(lexer_node_t *node);
void        add_command(t_cmd **list, t_cmd *cmd);
t_redirect  *add_redirect(t_redirect **list, t_redirect *node);
t_cmd       *new_command(char *cmd);
t_redirect *new_redirect(char *name, char *heredoc, t_redir_type type);
void    handle_command(lexer_node_t *node);

/* ======================= Helper Functions ========================== **/
int	    ft_strcmp(const char *s1, const char *s2);
char    *get_next_line(int fd);

#endif