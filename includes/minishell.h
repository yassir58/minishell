#ifndef MINISHELL_H
#define MINISHELL_H


# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <paths.h>

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
#define READ_END 0
#define WRITE_END 1

// Builtings

#define B1 "echo"
#define B2 "cd"
#define B3 "pwd"
#define B4 "export"
#define B5 "unset"
#define B6 "env"
#define B7 "exit"


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



typedef struct s_exec_node
{
    t_node_type type;
    t_cmd_node *cmd;
    bool piped;
    bool builtin;
    struct s_exec_node *next;
    struct s_exec_node *prev;
    int *pipe;
} t_exec_node;


typedef struct env_list_s 
{
    char *variable_name;
    char *value;
    struct env_list_s *next;
} env_list_t;


typedef struct shell_args_s
{
    char *prompt;
    char *line;
    int **fds_table;
    env_list_t *env_list;
    lexer_node_t *lexer_list;
    t_exec_node *exec_node;
} shell_args_t;

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
void validate_first_node (lexer_node_t *node);
void invalid_operator (lexer_node_t *node);
void validate_last_node (lexer_node_t *node);
void validate_first_node (lexer_node_t *node);
void invalid_operator (lexer_node_t *node);
void validate_last_node (lexer_node_t *node);
void handle_piped_command (shell_args_t *args);

/* ======================= Parser Functions ========================== **/

void        print_commands(t_cmd *list);
void        add_command(t_cmd **list, t_cmd *cmd);
t_redirect  *add_redirect(t_redirect **list, t_redirect *node);
t_cmd       *new_command(char *cmd);
t_redirect *new_redirect(char *name, char *heredoc, t_redir_type type);
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
int commands_number(t_cmd *list);
char    **get_commands(t_cmd *cmds);
int number_of_el(char **cmds);
void    display(char **cmds);
void    print_exec_node(t_exec_node *list);
void handle_nonbuiltin (shell_args_t *args, t_exec_node *exec_node);
void handle_builtin (shell_args_t *args, t_exec_node *exec_node);
int execution_function (shell_args_t *args);
int builtin_routine (shell_args_t *args, t_exec_node *exec_node);
void exec_command (shell_args_t *args, t_exec_node *exec_node);
/* ======================= Helper Functions ========================== **/
int	    ft_strcmp(const char *s1, const char *s2);

char    *get_next_line(int fd);

#endif

/** 
 * Node 1
 * 
 * 
 * 
*/

/* ============================= exection ================================= */

///////// testing ////////
void    test_exec_node (t_exec_node *node);
char	*check_access(char *command);
char	**paths_table(char *path);
char    *update_prompt (shell_args_t *args);
void print_fd_table (shell_args_t *args);

/* ======================= Parser Functions ========================== **/

void        print_commands(t_cmd *list);


/* ======================= Helper Functions ========================== **/

// - Function that should be added to the libft library.
int	    ft_strcmp(const char *s1, const char *s2);

// - Function related to string convesion.
int     commands_number(t_cmd *list);
char    **get_commands(t_cmd *cmds);
int     number_of_el(char **cmds);
void    display(char **cmds);

// - Function related to redirection lists.
t_redirect *last_redirect(t_redirect *lst);
t_redirect  *add_redirect(t_redirect **list, t_redirect *node);
t_redirect *new_redirect(char **names, char *heredoc, t_redir_type type);

// - Function realted to commands lists.
void        add_command(t_cmd **list, t_cmd *cmd);
t_cmd       *new_command(char *cmd);
t_cmd       *last_command(t_cmd *lst);
t_cmd_node *command_node(t_redirect *redirlist, t_cmd *cmdlist);

// - Functions related to parsing core.
t_exec_node *parse(lexer_node_t *node);
t_exec_node *parse_command(lexer_node_t **node);

// - Functions related to execution node.
t_exec_node *new_exec_cmd(t_cmd_node *cmd, bool piped);
t_exec_node *last_exec_node(t_exec_node *list);

// - Functions can be used as utility.
bool is_builtin(t_cmd_node *cmd);
int	advanced_strcmp(char *s1, char *s2);
int     count_filenames(lexer_node_t *node);
char   **filenames_table(lexer_node_t **node, int files);

// - Functions can be used as helpers.
int check_node(lexer_node_t *node, char *operator);
int check_redirect(lexer_node_t *node);
int redirect_type(lexer_node_t *node);

// - Function can be used for printing.
void    print_exec_node(t_exec_node *list);
void    print_redirects(t_redirect *list);
void    print_commands(t_cmd *list);

// - Just a testing function.
char    *prompt(void);

#endif

/** 
 * Node 1
 * 
 * 
 * 
*/
=======
/// pipes
void link_pipes (shell_args_t *args);
void handle_piped_command (shell_args_t *args);
void init_fds (shell_args_t *args);
void handle_first_command (shell_args_t *args, t_exec_node *exec_node);
void handle_last_command (shell_args_t *args, t_exec_node *exec_node);
void handle_doubly_piped (shell_args_t *args, t_exec_node *exec_node);
void handle_simple_command (shell_args_t *args, t_exec_node *exec_node);
int **get_fd_table(shell_args_t *args);
int nodes_number (shell_args_t *args);
void close_fd_table (int **fd_table);
void link_pipes (shell_args_t *args);
void exec_command (shell_args_t *args, t_exec_node *exec_node);
