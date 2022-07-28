#include "../includes/minishell.h"

int handle_redir_input (shell_args_t *args, t_redirect *redirect_node)
{
    int fd;

    if (access(redirect_node->filename, (F_OK)))
    {
        printf ("%s no such file or directory \n", redirect_node->filename);
        return (-1);
    }
    fd = open (redirect_node->filename, O_RDONLY, 0644);
    if (fd == -1)
        return (exit_with_failure (args, "failed top opem file for reading\n"));
    
    return (fd);
}

int handle_redir_output (shell_args_t *args, t_redirect *redirect_node)
{
    int fd;
 
    fd = open (redirect_node->filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if (fd == -1)
        return (exit_with_failure (args, "failed to open file for writing\n"));

    return (fd);
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

int handle_redirections (shell_args_t *args , t_exec_node *exec_node, int *infile, int *outfile)
{
    t_redirect *temp;

    temp = exec_node->cmd->redir_list;
    while (temp)
    {
        if (temp->type == REDIRIN)
            *infile = handle_redir_input (args, temp);
        else if (exec_node->cmd->redir_list->type == REDIROUT)
            *outfile = handle_redir_output (args, temp);
        if (*infile == -1 || *outfile == -1)
            return (-1);
        temp = temp->next;
    }
    // dup2 (in, STDIN_FILENO);
    // dup2 (outfile, STDOUT_FILENO);
    // else if (tmp->type == APPEND)
    //     err = handle_redir_append (args, tmp);
    // else if (tmp->type == HEREDOC)
    //     err =handle_herdoc (args, tmp);
    // if (err == EXIT_FAILURE)
    return (0);
}

