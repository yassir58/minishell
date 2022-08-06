/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 11:22:38 by ochoumou          #+#    #+#             */
/*   Updated: 2022/08/06 14:38:59 by ochoumou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define OPERATOR 0
# define WORD 1
# define SINGLE_QUOTED_SEQUENCE 2
# define DOUBLE_QUOTED_SEQUENCE 3
# define VARIABLE 4
# define DELIMTERS "'\" "
# define OPERATORS ">|<"
# define TRUE 1
# define FALSE 0
# define READ_END 0
# define WRITE_END 1

typedef struct s_lexer_node
{
	int					token;
	char				*start;
	int					length;
	int					joinable;
	int					closed;
	int					invalid;
	struct s_lexer_node	*next;
}	t_lexer_node;

typedef enum s_node_type
{
	CMD_NODE,
	PIPE_NODE
}	t_node_type;

typedef enum s_redir_type
{
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redirect
{
	t_redir_type		type;
	char				*filename;
	char				*heredoc_content;
	int					token;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_cmd {
	char			*cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_cmd_node
{
	t_cmd		*cmds;
	t_redirect	*redir_list;
}	t_cmd_node;

typedef struct s_exec_node
{
	t_cmd_node			*cmd;
	bool				piped;
	bool				builtin;
	bool				status;
	struct s_exec_node	*next;
	struct s_exec_node	*prev;
}	t_exec_node;

typedef struct s_env_list
{
	char				*variable_name;
	char				*value;
	int					index;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_shell_args
{
	char			*prompt;
	char			*line;
	unsigned char	status;
	char			**env;
	t_env_list		*env_list;
	t_lexer_node	*lexer_list;
	t_exec_node		*exec_node;
}	t_shell_args;

typedef struct s_shell_data
{
	int				heredoc_status;
	int				fork_status;
	unsigned char	exit_code;
}	t_shell_data;

typedef struct s_exec_utils
{
	int	**fds;
	int	indx;
	int	id;
	int	infile;
	int	outfile;
}	t_exec_utils;

t_shell_data	*g_data;

/**
* @brief Global data initialization
* @description: Functions that helps initialize the global data
*/

t_exec_utils	*init_exec_utils(void);
t_shell_data	*init_global(void);
t_shell_args	*init_args(char *env[]);

/** 
 * @brief Lexer functions
 * @description: Functions that helps create tokens list 
*/

t_lexer_node	*lexer(t_shell_args *args, char *line);
t_lexer_node	*handle_regular(char *line, int *index);
t_lexer_node	*handle_delim(char *line, int *index);
t_lexer_node	*handle_operator(char *line, int *index);
t_lexer_node	*init_node(void);

/**
 * @brief Variable expansion
 * @description: Functions that expand variables
 */

char			*expand_variable(t_shell_args *args, char *str);
char			*extract_var_name(char *str, int *index);
char			*get_variable_value(t_shell_args *args, char *str, int *i);
char			*ft_getenv(t_shell_args *args, char *varName);
char			*push_char(char *str, char c);

/**
 * @brief Syntax validation
 * @description: Functions that helps validate the token list
 */

int				syntax_error(void);
int				syntax_validation(t_shell_args *args);
int				validate_first_node(t_shell_args *args);
int				validate_last_node(t_shell_args *args);
int				invalid_operator(t_lexer_node *node);

/**
 * @brief Token list
 * @description: Functions that add tokens to the lexer list.
 */
void			handle_quote(char *line, int *index, t_lexer_node **node);
void			push_to_list(t_lexer_node **head, t_lexer_node *node);
void			create_token_list(t_shell_args *args, \
t_lexer_node **head, t_lexer_node *temp);

/**
 * @brief Handle Env variable
 * @description: Functions that handles env variables: add, delete, append.
 */

t_env_list		*get_env_list(char *env[]);
t_env_list		*create_env_node(char *envStr, int index);
void			push_env_node(t_env_list **head, t_env_list *node);
void			test_env_list(t_env_list *list);

/**
 * @brief Parser
 * @description: Functions that parse the tokens list
 */

t_exec_node		*parse(t_shell_args *args, t_lexer_node *node);
t_exec_node		*parse_command(t_shell_args *args, t_lexer_node **node);
int				check_node(t_lexer_node *node, char *operator);
int				check_redirect(t_lexer_node *node);
int				redirect_type(t_lexer_node *node);
int				handle_ctrl(t_shell_args *args, t_redirect *tmp, \
t_lexer_node *word);
void			get_file_content(t_redirect *tmp);
void			handle_heredoc(t_shell_args *args, t_redirect *node, \
int fd, t_lexer_node *word);
bool			is_builtin(t_cmd_node *cmd);

/**
 * @brief Clean up
 * @description: Function that cleans memory leaks
 */

void			free_parser(t_exec_node **lst);
void			free_string_table(char **table);
void			free_lexer(t_lexer_node **lst);
char			*free_joined(char *str);
void			free_list(t_lexer_node *node);
void			free_tab(char *tab[]);

/**
 * @brief Printing
 * @description: Function that print node
 */

void			print_exec_node(t_exec_node *list);
void			print_redirects(t_redirect *list);
void			print_commands(t_cmd *list);
void			print_export_list(t_env_list *list);
void			print_node_lex(t_lexer_node *node);
void			testing(t_lexer_node *node);

/**
 * @brief Convert string
 * @description: Function that display and convert string tables
 */

int				commands_number(t_cmd *list);
int				number_of_el(char **cmds);
char			**get_commands(t_cmd *cmds);
void			display(char **cmds);

/**
 * @brief Commands List
*/

void			add_command(t_cmd **list, t_cmd *cmd);
t_cmd			*new_command(char *cmd);
t_cmd			*last_command(t_cmd *lst);
t_cmd_node		*command_node(t_redirect *redirlist, t_cmd *cmdlist);

/**
 * @brief Redirections List
*/

t_redirect		*last_redirect(t_redirect *lst);
t_redirect		*add_redirect(t_redirect **list, t_redirect *node);
t_redirect		*new_redirect(char *name, char *heredoc, t_redir_type type, \
int token);

/**
 * @brief Execution List
*/

t_exec_node		*new_exec_cmd(t_cmd_node *cmd, bool piped, bool status);
t_exec_node		*last_exec_node(t_exec_node *list);

/**
 * @brief Shell setup and promopt
 * @description: Functions that will lunch the prompt and init signals
*/

char			*prompt(char *string);
char			*update_prompt(t_shell_args *args);
void			init_signals(void);

/**
 * @brief Utils
*/

int				advanced_strcmp(char *s1, char *s2);
char			*advanced_get_next_line(int fd, int status);
int				is_number(char *str);
int				check_space(char *str);

/**
* @brief Builtins
* @description: Builtin functions for the shell
*/

int				ft_export(t_exec_node *exec_node, t_env_list *list);
int				ft_unset(t_exec_node *exec_node, t_env_list **list);
int				ft_env(t_exec_node *exec_node, t_env_list *list);
int				ft_exit(t_exec_node *exec_node);
int				echo_function(t_shell_args *args, char *argv[], int argc);
int				cd_function(char *arg, t_env_list **env_list);
int				pwd_function(t_env_list *env_list);

/**
* @brief Builtin utils
* @description: Utils functions for the builtins
*/

void			cd_to_home(t_env_list *env_list);
void			handle_exit(char **cmds);
int				check_for_dots(char *arg, t_env_list *list);
int				update_pwd_env(t_env_list **list);
char			*get_pwd_env(t_env_list *list);
char			*get_pwd(t_env_list *env_list);

/**
* @brief Env list
* @description: Function to handle the env variables
*/

t_env_list		*search_env_variable(char *var, t_env_list *list);
t_env_list		*create_path_node(void);
void			print_env_list(t_env_list *list);
void			order_env_list(t_env_list *list);
void			print_export_list(t_env_list *list);
void			delete_env_variable(t_env_list **list, char *key);

/**
* @brief Execution
* @description: Function related to the execution phase
*/

char			**handle_absolue_path(char **path_table);
char			**handle_relative_path(char **path_table);
int				handle_piped_command(t_shell_args *args);
int				check_for_valid_option(char *option);
void			exec_command(t_shell_args *args, t_exec_node *exec_node);
void			handle_nonbuiltin(t_shell_args *args, t_exec_node *exec_node);
int				handle_builtin(t_shell_args *args, t_exec_node *tmp, int **fds, \
int indx);
int				execution_chain(t_shell_args *args);
int				builtin_routine(t_shell_args *args, t_exec_node *exec_node, \
int infile, int outfile);
void			test_exec_node(t_exec_node *node);
char			*check_access(t_shell_args *args, char *command, \
char *path, int *status);
char			**paths_table(char *path);
void			init_fds(t_shell_args *args);
void			handle_first_command(int indx, int **fds_table);
void			handle_last_command(int indx, int **fds_table);
void			handle_doubly_piped(int indx, int **fds_table);
int				nodes_number(t_shell_args *args);
void			close_fd_table(int **fd_table);
int				**open_fd_table(int size, t_shell_args *args);
void			exec_command(t_shell_args *args, t_exec_node *exec_node);
void			close_unused_fds(int **fds_table, int used);
void			close_unused_fds_2(int **fds_table, int used1, int used2);
void			init_old_pwd(t_env_list **env_list);
void			get_children_status(void);
int				handle_redir_input(t_shell_args *args, \
t_redirect *redirect_node, int *err);
int				handle_redir_output(t_shell_args *args, \
t_redirect *redirect_node, int *err);
int				handle_redir_append(t_shell_args *args, \
t_redirect *redirect_node, int *err);
int				handle_redirections(t_shell_args *args, t_exec_node *exec_node, \
int *infile, int *outfile);
void			*allocation_err(void);
int				open_pipe(int *fd, t_shell_args *args);
int				close_fd(int fd);
int				exit_with_failure(t_shell_args *args, char *err_message);
int				fork_child(t_shell_args *args);
void			init_command(t_shell_args *args);
int				get_status(int pid);
void			check_for_valid_command(t_exec_node *exec_node);
void			command_exist(t_exec_node *exec_node);
int				handle_simple_command(t_shell_args *args);
void			shell_err(char *command, int status, int path_check);
int				builtin_err(char *err, char *arg);
void			link_pipes(t_exec_node *tmp, int **fds, int indx);
int				exec_piped_commands(t_shell_args *args);
char			**get_path(t_shell_args *args, char **cmds, \
int *status, int *path_check);
int				handle_cd(t_shell_args *args, char **cmds);
int				access_status(char *cmd, int *status);
int				cd_prev_pwd(t_env_list *env_list);
void			redir_err(char *filename, char *err_message);
void			link_rediriction_pipes(int infile, int outfile);
int				handle_one_builtin_cmd(t_shell_args *args, \
int infile, int outfile);
void			exec_cmd(t_shell_args *args, t_exec_node *tmp, \
t_exec_utils *utils);
void			add_exit_var(t_env_list **env_list);
void			set_exit_status(t_env_list **env_list, unsigned char exit_code);
int				env_size(t_env_list *list);
char			**get_env_table(t_env_list *list);
char			*expand_word(t_shell_args *args, char *str);
char			*handle_expand(t_shell_args *args, t_lexer_node *temp);
int				isDir(char *filename);
char			*get_env_path(t_shell_args *args);
void			init_env_list(t_env_list **env_list);
void			echo_print(t_shell_args *args, char *str);

#endif
