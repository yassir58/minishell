#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
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

// Builtins
#define B1 "echo"
#define B2 "cd"
#define B3 "pwd"
#define B4 "export"
#define B5 "unset"
#define B6 "env"
#define B7 "exit"

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

typedef struct s_redirect 
{
    t_redir_type type;
    char **filenames;
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

typedef struct s_exec_node
{
    t_node_type type;
    t_cmd_node *cmd;
    bool piped;
    bool builtin;
    struct s_exec_node *next;
    struct s_exec_node *prev;
} t_exec_node;

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

/* ======================= Parser Functions ========================== **/

void        print_commands(t_cmd *list);
void        add_command(t_cmd **list, t_cmd *cmd);
t_redirect  *add_redirect(t_redirect **list, t_redirect *node);
t_cmd       *new_command(char *cmd);
t_redirect *new_redirect(char **names, char *heredoc, t_redir_type type);
void    handle_command(lexer_node_t *node);
t_cmd *last_command(t_cmd *lst);
t_redirect *last_redirect(t_redirect *lst);
t_exec_node *parse_command(lexer_node_t **node);
t_exec_node *new_exec_cmd(t_cmd_node *cmd, bool piped);
t_exec_node *new_exec_pipe();
t_exec_node *last_exec_node(t_exec_node *list);
t_exec_node   *parse(lexer_node_t *node);
bool is_builtin(t_cmd_node *cmd);
t_cmd_node *command_node(t_redirect *redirlist, t_cmd *cmdlist);
int	advanced_strcmp(char *s1, char *s2);

/* ======================= Helper Functions ========================== **/
int	    ft_strcmp(const char *s1, const char *s2);
void    display(char **cmds);
char    **get_commands(t_cmd *cmds);
char    *get_next_line(int fd);

#endif

/** 
 * Node 1
 * 
 * 
 * 
*/