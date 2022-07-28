#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <paths.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>


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

int heredoc_status;

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
    bool status;
    struct s_exec_node *next;
    struct s_exec_node *prev;
} t_exec_node;

typedef struct env_list_s 
{
    char *variable_name;
    char *value;
    int index;
    struct env_list_s *next;
} env_list_t;

typedef struct shell_args_s
{
    char *prompt;
    char *line;
    int **fds_table;
    unsigned char exit_code;
    env_list_t *env_list;
    lexer_node_t *lexer_list;
    t_exec_node *exec_node;
    int shell_level;
    char **env;
} shell_args_t;


lexer_node_t *lexer (char *line);
lexer_node_t *handle_regular (char *line, int *index);
lexer_node_t *handle_delim (char *line, int *index);
lexer_node_t *handle_operator (char *line, int *index);
char **handle_absolue_path (char **path_table);
char **handle_relative_path (char **path_table);
void handle_quote (char *line, int *index, lexer_node_t **node);
void push_to_list (lexer_node_t **head, lexer_node_t *node);
void create_token_list (lexer_node_t **head, lexer_node_t *temp);
void free_list(lexer_node_t *node);
void print_token (int token);
void testing (lexer_node_t *node);
lexer_node_t *init_node ();
int syntax_error (shell_args_t *args);
int syntax_validation (shell_args_t *args);
void check_word (lexer_node_t *tokens_list);
char *expand_variable (char *str);
char *extract_var_name (char *str, int *index);
char *get_variable_value (char *str, int *i);
char *push_char (char *str, char c);
env_list_t *get_env_list (char *env[]);
env_list_t *create_env_node (char *envStr, int index);
void push_env_node (env_list_t **head, env_list_t *node);
void free_tab (char *tab[]);
int pwd_function (env_list_t *env_list);
void test_env_list (env_list_t *list);
int cd_function (char *arg, int flag, env_list_t **env_list);
void cd_to_home (env_list_t *env_list);
int check_for_dots (char *arg, env_list_t *list);
char *get_pwd_env (env_list_t *list);
int update_pwd_env (env_list_t **list);
char *get_pwd (env_list_t *env_list);
int echo_function (char *argv[], int argc);
int invalid_operator (shell_args_t *args, lexer_node_t *node);
int validate_first_node (shell_args_t *args);
int validate_last_node (shell_args_t *args);
int handle_piped_command (shell_args_t *args);
int check_for_valid_option (char *option);
/* ======================= Parser Functions ========================== **/

// void        print_commands(t_cmd *list);
// void        add_command(t_cmd **list, t_cmd *cmd);
// t_redirect  *add_redirect(t_redirect **list, t_redirect *node);
// t_cmd       *new_command(char *cmd);
// void    handle_command(lexer_node_t *node);
// t_cmd *last_command(t_cmd *lst);
// t_redirect *last_redirect(t_redirect *lst);
// t_exec_node *parse_command(lexer_node_t **node);
// t_exec_node *new_exec_cmd(t_cmd_node *cmd, bool piped);
// t_exec_node *new_exec_pipe();
// t_exec_node *last_exec_node(t_exec_node *list);
// t_exec_node   *parse(lexer_node_t *node);
// bool is_builtin(t_cmd_node *cmd);
// t_cmd_node *command_node(t_redirect *redirlist, t_cmd *cmdlist);
// int	advanced_strcmp(char *s1, char *s2);
// int commands_number(t_cmd *list);
// char    **get_commands(t_cmd *cmds);
// int number_of_el(char **cmds);
// void    display(char **cmds);
// void    print_exec_node(t_exec_node *list);
void handle_nonbuiltin (shell_args_t *args, t_exec_node *exec_node);
int handle_builtin (shell_args_t *args, t_exec_node *tmp, int **fds, int indx);
int execution_chain (shell_args_t *args);
int builtin_routine (shell_args_t *args, t_exec_node *exec_node);
void exec_command (shell_args_t *args, t_exec_node *exec_node);
int check_node(lexer_node_t *node, char *operator);
int check_redirect(lexer_node_t *node);
int redirect_type(lexer_node_t *node);
char   **filenames_table(lexer_node_t **node, int files);
int     count_filenames(lexer_node_t *node);
/* ======================= Helper Functions ========================== **/
int	    ft_strcmp(const char *s1, const char *s2);
char    *get_next_line(int fd);


int    ft_unset(t_exec_node *exec_node, env_list_t *list, shell_args_t *args);
int ft_env(t_exec_node *exec_node, env_list_t *list, shell_args_t *args);
void handle_exit(char **cmds, shell_args_t *args);
int ft_exit(t_exec_node *exec_node, env_list_t *list, shell_args_t *args);
env_list_t *search_env_variable(char *var, env_list_t *list);
void    delete_env_variable(char *var, env_list_t *list);
void print_env_list (env_list_t *list);
int     check_space(char *str);
char    *prompt(char *string);

///////// testing ////////
void    test_exec_node (t_exec_node *node);
char	*check_access(char *command, char *path, int *status);
char	**paths_table(char *path);
char    *update_prompt (shell_args_t *args);

/* ======================= Parser Functions ========================== **/

void        print_commands(t_cmd *list);

// - Function related to parser handler


void    handle_heredoc(t_redirect *node, int fd, lexer_node_t *word);

// - Function related to string convesion.
int     commands_number(t_cmd *list);
char    **get_commands(t_cmd *cmds);
int     number_of_el(char **cmds);
void    display(char **cmds);

// - Function related to redirection lists.
t_redirect *last_redirect(t_redirect *lst);
t_redirect  *add_redirect(t_redirect **list, t_redirect *node);
t_redirect  *new_redirect(char *name, char *heredoc, t_redir_type type);

// - Function related to commands lists.
void        add_command(t_cmd **list, t_cmd *cmd);
t_cmd       *new_command(char *cmd);
t_cmd       *last_command(t_cmd *lst);
t_cmd_node *command_node(t_redirect *redirlist, t_cmd *cmdlist);

// - Functions related to parsing core.
t_exec_node   *parse(shell_args_t *args, lexer_node_t *node);
t_exec_node *parse_command(lexer_node_t **node);

// - Functions related to execution node.
t_exec_node *new_exec_cmd(t_cmd_node *cmd, bool piped, bool status);
t_exec_node *last_exec_node(t_exec_node *list);

// - Functions can be used as utility.
bool is_builtin(t_cmd_node *cmd);
/**
 * @brief This function will compare two strings regardless if one of the strings is
 * capitale letters
 * @param s1 The source string that you want to compare
 * @param s2 The destination string that you want to compare
 * @return int 
 */
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
void    print_env_list (env_list_t *list);

// - History function.
char    *prompt(char *string);

// - Function related to the ENV variables.
env_list_t  *search_env_variable(char *var, env_list_t *list);
void        print_env_list (env_list_t *list);
void        order_env_list(env_list_t *list);
void    print_unsorted_env(env_list_t *list);



// - Testing

void    print_node_lex(lexer_node_t *node);

// - Functions related to the parser clean up.
void	free_parser(t_exec_node **lst);
void	free_string_table(char **table);

// - Util functions for builtins
char	*advanced_get_next_line(int fd, int status);
int     is_number(char *str);

// - Functions related to the signals handling

void    init_signals(void);

// void handle_piped_command (shell_args_t *args);
void init_fds (shell_args_t *args);
void handle_first_command (int indx, int **fds_table);
void handle_last_command (int indx, int **fds_table);
void handle_doubly_piped (int indx, int **fds_table);
int nodes_number (shell_args_t *args);
void close_fd_table (int **fd_table);
int **open_fd_table (int size , shell_args_t *args);
void exec_command (shell_args_t *args, t_exec_node *exec_node);
void close_unused_fds (int **fds_table , int used);
void close_unused_fds_2 (int **fds_table, int used1, int used2);
env_list_t *create_path_node (void);
void init_old_pwd (env_list_t **env_list);
int get_childer_status (void);
/// redirections
int handle_redir_input (shell_args_t *args, t_redirect *redirect_node);
int handle_redir_output (shell_args_t *args, t_redirect *redirect_node);
int handle_redir_append (shell_args_t *args, t_redirect *redirect_node);
int handle_herdoc (shell_args_t *args ,t_redirect *redirect_node);
int handle_redirections (shell_args_t *args,t_redirect *redir_list);
//////// general utils
void *allocation_err (void);
int open_pipe (int *fd, shell_args_t *args);
int close_fd (int fd);
int exit_with_failure (shell_args_t *args, char *err_message);
int fork_child (shell_args_t *args);
int init_command (shell_args_t *args);
int get_status (int pid);
void check_for_valid_command (t_exec_node *exec_node);
void command_exist (t_exec_node *exec_node);
int handle_simple_command (shell_args_t *args);
void shell_err (char *command, int status);
int builtin_err (char *err, char *arg);
void link_pipes (t_exec_node *tmp, int **fds, int indx);
int test_piped_commands (shell_args_t *args);
char **get_path (shell_args_t *args, char **cmds, int *status);
int handle_cd (shell_args_t *args, char **cmds);
int access_status (char *cmd, int *status);

#endif
