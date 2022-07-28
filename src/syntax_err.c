#include "../includes/minishell.h"


int syntax_error (shell_args_t *args)
{
    ft_putstr_fd ("Syntax error \n", 2);
    return (258);
    
}

int syntax_validation (shell_args_t *args)
{
    lexer_node_t *tmp;
    int last_node;
    int status;

    tmp = args->lexer_list ;
    status = validate_first_node (args);
    if (!status)
        status = validate_last_node (args);
    if (status)
        return (status);
    while (tmp)
    {
        status = invalid_operator (args, tmp);
        if (status)
            return (status);
        if (tmp->token == DOUBLE_QUOTED_SEQUENCE ||
            tmp->token == SINGLE_QUOTED_SEQUENCE)
        {
            if (tmp->closed == FALSE)
                return (syntax_error (args));
        }
        tmp = tmp->next;
    }
    return (0);
}

int validate_first_node (shell_args_t *args)
{
    if (args->lexer_list->token == OPERATOR)
    {
        if (!ft_strcmp (args->lexer_list->start, "|"))
             return (syntax_error (args));
        else if (args->lexer_list->next == NULL)
            return (syntax_error (args));
    }
    return (0);
}

int invalid_operator (shell_args_t *args, lexer_node_t *node)
{
    if (node->token == OPERATOR)
    {
        if (node->invalid == TRUE)
            return (syntax_error (args));
        if (ft_strcmp (node->start, "|"))
        {
            if (node->next && node->next->token == OPERATOR)
            {
                if ((!ft_strcmp (node->start, ">") && !ft_strcmp (node->next->start, "<")) ||
                    (!ft_strcmp (node->next->start, "|")))
                    return (syntax_error (args));
            }
        }
        else if (node->next)
        {
            if (!ft_strcmp (node->next->start, "|"))
                return (syntax_error (args));
        }
    }
    return (0);
}

int validate_last_node (shell_args_t *args)
{
    lexer_node_t *tmp ;

    tmp = args->lexer_list;
    while (tmp->next)
        tmp = tmp->next;
    if (tmp->token == OPERATOR)
        return (syntax_error (args));
    return (0);
}