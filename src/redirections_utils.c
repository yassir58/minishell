#include "../includes/minishell.h"

int handle_redir_input (shell_args_t *args, t_redirect *redirect_node)
{
    int fd;
  
    fd = open (redirect_node->filename, O_RDONLY, 0644);
    if (fd == -1)
        return (exit_with_failure (args, "no such file or directory\n"));
    else
        dup2 (fd, STDIN_FILENO);
    return (0);
}

int handle_redir_output (shell_args_t *args, t_redirect *redirect_node)
{
    int fd;
    
    fd = open (redirect_node->filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
        return (exit_with_failure (args, "failed to open file for writing\n"));
    else
        dup2 (fd , STDOUT_FILENO);
    return (0);
}

int handle_redir_append (shell_args_t *args, t_redirect *redirect_node)
{
    int fd;
    
    fd = open (redirect_node->filename, O_WRONLY|O_APPEND|O_CREAT, 0644);
    if (fd == -1)
        return (exit_with_failure (args, "failed to open file for append\n"));
    else
        dup2 (fd , STDOUT_FILENO);
    return (0);
}

int handle_herdoc (shell_args_t *args ,t_redirect *redirect_node)
{
    int fds[2];
    int err;

    if (pipe (fds) == -1)
        return (exit_with_failure (args, "failed to open pipe \n"));
    if (redirect_node->heredoc_content)
    {
        dup2 (fds[READ_END], STDIN_FILENO);
        close_fd (fds[READ_END]);
        err = write (fds[WRITE_END], redirect_node->heredoc_content, ft_strlen (redirect_node->heredoc_content));
        if (err == -1)
            return (exit_with_failure (args, "failed to write to pipe\n"));
        close_fd (fds[WRITE_END]);
    }
    return (0);
}

int handle_redirections (shell_args_t *args ,t_redirect *redir_list)
{
    t_redirect *tmp;
    int err;


    tmp = redir_list;
    err = 0;
    while (tmp)
    {
        if (tmp->type == REDIRIN)
            err = handle_redir_input (args, tmp);
        else if (tmp->type == REDIROUT)
            err = handle_redir_output (args, tmp);
        else if (tmp->type == APPEND)
            err = handle_redir_append (args, tmp);
        else if (tmp->type == HEREDOC)
            err =handle_herdoc (args, tmp);
        if (err == EXIT_FAILURE)
            break;
        tmp = tmp->next;
    }
    return (err);
}
