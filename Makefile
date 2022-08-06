# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 18:42:41 by ochoumou          #+#    #+#              #
#    Updated: 2022/08/06 19:10:09 by ochoumou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/main.c src/builtins/ft_cd.c src/builtins/ft_echo.c src/builtins/ft_env.c src/builtins/ft_exit.c src/builtins/ft_export.c src/builtins/ft_helpers.c src/builtins/ft_pwd.c \
src/builtins/ft_unset.c src/builtins/ft_validate.c src/cleanup/extra_free.c src/cleanup/free.c src/execution/check_cmd.c src/execution/exec_helpers.c src/execution/exec_list.c \
src/execution/exec_utils.c src/execution/execution.c src/execution/execution_additional.c src/execution/execution_init.c src/execution/execution_utils.c src/execution/redirections_add.c \
src/execution/redirections_utils.c src/init/history.c src/init/signal_handler.c src/lists/command_list.c src/lists/env_list.c src/lists/redir_list.c src/parser/lexer.c src/parser/lexer_additional.c \
src/parser/lexer_utils.c src/parser/parse_helper.c src/parser/parse_heredoc.c src/parser/parse_printer.c src/parser/parse_utils.c src/parser/parser.c src/parser/syntax_err.c src/utils/env_utils.c \
src/utils/general_utils.c src/utils/gnl.c src/utils/init_data.c src/utils/string_convert.c src/utils/utils.c

OBJS= $(SRCS:.c=.o)
NAME = minishell
HEADERS = ./includes/minishell.h
LIBNAME = ./libft/libft.a
INCLUDES= "-I/Users/ochoumou/.brew/opt/readline/include"
READLINE= -lreadline -L/Users/ochoumou/.brew/opt/readline/lib

CC = gcc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(READLINE) $(LIBNAME)

%.o : %.c $(HEADERS)
	$(CC) $(FLAGS)  -c $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all