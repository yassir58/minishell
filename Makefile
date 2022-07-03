
SRCS=main.c lexer.c lexer_additional.c utils.c  syntax_err.c lexer_utils.c parse_helper.c parse_utils.c ft_strcmp.c testing.c  execution.c env_utils.c builtins.c \
builtins_utils.c check_cmd.c execution_utils.c execution_additional.c general_utils.c  command_list.c exec_list.c history.c parse_printer.c redir_list.c string_convert.c \
parser.c redirections_utils.c env_list.c builtins_additional.c
RED=\033[0;31m
NC=\033[0m
LIBFTDIR=./libft/
SRCDIR=./src/
INCLUDE=./includes
OBJS=$(addprefix $(SRCDIR), $(SRCS:.c=.o))
PROGNAME=minishell
LIBNAME=libft.a
CFALGS=-Wall -Wextra -Werror -g
LDFLAGS= -L./libft -lft -L/usr/include  -lreadline 
CC=gcc

all:$(PROGNAME)

%.o:$(SRCDIR)/%.c
	$(CC) -c $(CFALGS) -o $(SRCDIR)/$@ $<

$(PROGNAME):$(OBJS) $(INCLUDE)/minishell.h
	@printf "${RED}building libft ...${NC}\n"
	@cd ./libft && make && cd ..
	$(CC) $(CFALGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	@cd ./libft && make clean && cd ..
	rm -rf $(OBJS)

fclean:clean
	@cd ./libft && make fclean && cd ..
	rm -rf $(PROGNAME)  $(LIBNAME)

re:fclean all