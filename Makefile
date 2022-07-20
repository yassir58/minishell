SRCDIR=./src/
SRCS = main.c lexer.c lexer_additional.c utils.c  syntax_err.c lexer_utils.c testing.c  execution.c env_utils.c builtins.c builtins_utils.c builtins_additional.c check_cmd.c execution_utils.c \
	command_list.c exec_list.c parse_helper.c parse_printer.c parse_utils.c parser.c redir_list.c string_convert.c history.c signal_handler.c gnl.c
OBJS=$(addprefix $(SRCDIR), $(SRCS:.c=.o))
NAME = minishell
HEADERS = ./includes/minishell.h
LIBNAME = ./libft/libft.a
INCLUDES= -I/Users/ochoumou/.brew/opt/readline/include
READLINE= -lreadline -L/Users/ochoumou/.brew/opt/readline/lib

CC = gcc
# FLAGS = -Wall -Wextra -Werror

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