SRCDIR=./src/
SRCS = main.c lexer.c lexer_additional.c utils.c  syntax_err.c lexer_utils.c parse_helper.c parse_utils.c testing.c  execution.c env_utils.c builtins.c \
builtins_utils.c check_cmd.c execution_utils.c execution_additional.c general_utils.c  command_list.c exec_list.c history.c parse_printer.c redir_list.c string_convert.c \
parser.c redirections_utils.c env_list.c builtins_additional.c builtins_helper.c execution_init.c gnl.c signal_handler.c free.c
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