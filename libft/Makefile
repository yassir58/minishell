# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ochoumou <ochoumou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/10 16:58:49 by yelatman          #+#    #+#              #
#    Updated: 2022/06/29 15:46:02 by ochoumou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=libft.a
CC=gcc
CFLAGS= -Wall -Wextra -Werror
RM=rm -f
SRC = ft_atoi.c ft_isalpha.c  ft_itoa.c ft_memmove.c ft_putnbr_fd.c \
	  ft_strdup.c ft_strlcpy.c ft_strnstr.c  ft_tolower.c \
      ft_bzero.c ft_isascii.c ft_memchr.c ft_memset.c ft_putstr_fd.c \
	  ft_striteri.c ft_strlen.c ft_strrchr.c ft_toupper.c \
      ft_calloc.c ft_isdigit.c ft_memcmp.c ft_putchar_fd.c ft_split.c \
	  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_strcmp.c ft_isspace.c\
      ft_isalnum.c ft_isprint.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcat.c ft_strncmp.c ft_substr.c
BONUS_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			 ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			 ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRCS:.c=.o)
HEADER = libft.h
$(NAME): $(OBJ) $(HEADER) 
		ar -rc $(NAME) $(OBJ)
%.o: %.c
		$(CC) $(CFLAGS) -c $<
all: $(NAME)

bonus: $(BONUS_OBJ) $(HEADER)
	ar -rc $(NAME) $(BONUS_OBJ)

clean:
		$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

