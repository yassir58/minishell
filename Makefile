<<<<<<< HEAD
<<<<<<< HEAD
SRCS=main.c lexer.c lexer_additional.c utils.c
=======
SRCS=main.c lexer.c lexer_additional.c utils.c syntax_err.c
>>>>>>> 5418f058d244d274334386e9883c6e13fea4653b
RED=\033[0;31m
NC=\033[0m
LIBFTDIR=./libft/
SRCDIR=./src/
INCLUDE=./includes
OBJS=$(addprefix $(SRCDIR), $(SRCS:.c=.o))
<<<<<<< HEAD
=======
SRCS=exec.c main_prog.c parsing.c additional.c utils.c
LIBFTSRCS=$(wildcard libft/*.c)
LIBFTOBJS=$(LIBFTSRCS:.c=.o)
OBJS=$(SRCS:.c=.o)
>>>>>>> parsing phase completed, command validation, args validation
=======
>>>>>>> 5418f058d244d274334386e9883c6e13fea4653b
PROGNAME=minishell
LIBNAME=libft.a
CFALGS=-Wall -Wextra -Werror -g
LFLAGS= ...
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 5418f058d244d274334386e9883c6e13fea4653b
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

<<<<<<< HEAD
=======
LDFLAGS= libft.a -L/usr/include -lreadline 
CC=gcc

all:$(LIBNAME) $(PROGNAME)

%.o:%.c
	$(CC) $(CFALGS) -c $< -o $@
$(LIBNAME):$(LIBFTOBJS) ./libft/libft.h
	ar -rc $(LIBNAME) $(LIBFTOBJS)
$(PROGNAME):$(OBJS) minishell.h
	$(CC) $(CFALGS) $(OBJS) $(LDFLAGS) -o $@

clean:
	rm -rf $(OBJS) $(LIBFTOBJS)
fclean:clean
	rm -rf $(PROGNAME)  $(LIBNAME)
>>>>>>> parsing phase completed, command validation, args validation
=======
>>>>>>> 5418f058d244d274334386e9883c6e13fea4653b
re:fclean all