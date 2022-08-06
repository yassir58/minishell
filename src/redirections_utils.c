#include "../includes/minishell.h"

int handle_redir_input (t_shell_args *args, t_redirect *redirect_node, int *err)
{
    int fd;

    fd = access(redirect_node->filename, (F_OK));
    if (!ft_strcmp(redirect_node->filename, ""))
    {
        if (redirect_node->token == WORD)
            redir_err (redirect_node->filename, " :ambiguous redirect\n");
        else 
            redir_err (redirect_node->filename, " : No such file or directory\n");
        *err = 1;
        return (-1);
    }
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

int handle_redir_output (t_shell_args *args, t_redirect *redirect_node, int *err)
{
    int fd;

    if (!ft_strcmp(redirect_node->filename, ""))
    {
        if (redirect_node->token == WORD)
            redir_err (redirect_node->filename, " :ambiguous redirect\n");
        else 
            redir_err (redirect_node->filename, " : No such file or directory\n");
        *err = 1;
        return (-1);
    }
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

int handle_redir_append (t_shell_args *args, t_redirect *redirect_node,  int *err)
{
    int fd;
    
    if (!ft_strcmp(redirect_node->filename, ""))
    {
        if (redirect_node->token == WORD)
            redir_err (redirect_node->filename, " :ambiguous redirect\n");
        else 
            redir_err (redirect_node->filename, " : No such file or directory\n");
        *err = 1;
        return (-1);
    }
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

// int handle_herdoc (t_shell_args *args ,t_redirect *redirect_node)
// {
//     int fds[2];
//     int err;
//     int infile;

//     if (pipe (fds) == -1)
//         return (exit_with_failure (args, "failed to open pipe \n"));
//     if (redirect_node->heredoc_content)
//     {
//         err = write (fds[WRITE_END], redirect_node->heredoc_content, ft_strlen (redirect_node->heredoc_content));
//         if (err == -1)
//             return (exit_with_failure (args, "failed to write to pipe\n"));
//         close_fd (fds[WRITE_END]);
//     }
//     return (infile);
// }

int handle_redirections (t_shell_args *args , t_exec_node *exec_node, int *infile, int *outfile)
{
    t_redirect *temp;
    int err;
    int fds[2];
    int status;

    temp = exec_node->cmd->redir_list;
    err = 0;
    status = 0;
    while (temp)
    {
        if (temp->type == REDIRIN)
            *infile = handle_redir_input (args, temp , &status);
        else if (temp->type == REDIROUT)
            *outfile = handle_redir_output (args, temp, &status);
        else if (temp->type == APPEND)
            *outfile = handle_redir_append (args, temp, &status);
        else if (temp->type == HEREDOC)
        {
            pipe(fds);
            *infile = fds[READ_END];
            err = write (fds[WRITE_END], temp->heredoc_content, ft_strlen (temp->heredoc_content));
            close_fd (fds[WRITE_END]);
            if (err == -1)
                return (exit_with_failure (args, "failed to write to pipe\n"));
        }
        if (status)
            return (status);
        temp = temp->next;
    }
    return (status);
}

void redir_err (char *filename, char *err_message)
{
    char *err;

    err = ft_strjoin (filename , err_message);
    ft_putstr_fd (err, 2);
}


int isDir (char *filename)
{
    struct stat sfile;
    int accs;

    accs = access (filename, (F_OK));
    if (accs == -1)
        return (-1);
    stat("filename", &sfile);
    if (S_ISREG(sfile.st_mode) == 0)
        accs = 1;
    return (accs);
}