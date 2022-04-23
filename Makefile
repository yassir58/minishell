SRCS=exec.c main_prog.c parsing.c additional.c utils.c
LIBFTSRCS=$(wildcard libft/*.c)
LIBFTOBJS=$(LIBFTSRCS:.c=.o)
OBJS=$(SRCS:.c=.o)
PROGNAME=minishell
LIBNAME=libft.a
CFALGS=-Wall -Wextra -Werror -g
LFLAGS= ...
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
re:fclean all