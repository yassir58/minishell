#include "../includes/minishell.h"

int handle_redir_input (shell_args_t *args, t_redirect *redirect_node, int *err)
{
    int fd;

    fd = access(redirect_node->filename, (F_OK));
    if (fd == -1)
    {
        redir_err (redirect_node->filename, " : No such file or directory \n");
        *err = 1;
        return (-1);
    }
    else
    {
        fd = access (redirect_node->filename , (R_OK));
        if  (fd  == -1)
        {
            redir_err (redirect_node->filename, " : Permission denied\n");
            *err = 1;
            return (-1);
        }       
    }
    fd = open (redirect_node->filename, O_RDONLY, 0644);
    if (fd == -1)
        return (exit_with_failure (args, "failed top open file for reading\n"));
    return (fd);
}

int handle_redir_output (shell_args_t *args, t_redirect *redirect_node, int *err)
{
    int fd;

  
    fd = access (redirect_node->filename, (F_OK));
    if (fd != -1)
    {
        fd = access (redirect_node->filename, (F_OK | W_OK));
        if  (fd  == -1)
        {
            redir_err (redirect_node->filename, " : Permission denied\n");
            *err = 1;
            return (-1);
        }     
    }
    fd = open (redirect_node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return (exit_with_failure (args, "failed to open file for writing\n"));
    return (fd);
}

int handle_redir_append (shell_args_t *args, t_redirect *redirect_node,  int *err)
{
    int fd;
    
    fd = access (redirect_node->filename, (F_OK));
    if (fd != -1)
    {
        fd = access (redirect_node->filename, (F_OK | W_OK));
        if  (fd  == -1)
        {
            redir_err (redirect_node->filename, " : Permission denied\n");
            *err = 1;
            return (-1);
        }     
    }
    fd = open (redirect_node->filename, O_APPEND  | O_CREAT | O_RDWR , 0644);
    if (fd == -1)
        return (exit_with_failure (args, "failed to open file for append\n"));
    return (fd);
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
    int err;

    temp = exec_node->cmd->redir_list;
    err = 0;
    while (temp)
    {
        if (temp->type == REDIRIN)
            *infile = handle_redir_input (args, temp , &err);
        else if (temp->type == REDIROUT)
            *outfile = handle_redir_output (args, temp, &err);
        else if (temp->type == APPEND)
            *outfile = handle_redir_append (args, temp, &err);
        else if (temp->type == HEREDOC)
            err = handle_herdoc (args, temp);
        if (err)
            return (err);
        temp = temp->next;
    }
    return (err);
}

void redir_err (char *filename, char *err_message)
{
    char *err;

    err = ft_strjoin (filename , err_message);
    ft_putstr_fd (err, 2);
}
