# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 11:21:29 by erigonza          #+#    #+#              #
#    Updated: 2024/08/13 19:40:02 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS = ft_atoi.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_putchar_fd.c \
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_isalpha.c ft_isdigit.c \
	   ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memset.c \
	   ft_bzero.c ft_memcmp.c ft_memmove.c ft_memchr.c ft_memcpy.c ft_calloc.c \
	   ft_strlen.c ft_strdup.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	   ft_strnstr.c ft_strncmp.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	   ft_strmapi.c ft_striteri.c ft_strcmp.c ft_isspace.c \
	   ft_printf.c \
	   get_next_line.c get_next_line_utils.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	   ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
DIR_SRC = ./src
DIR_OBJ = $(DIR_SRC)/obj
OBJS = $(addprefix $(DIR_OBJ)/,$(SRCS:.c=.o))

AR		= ar rcs
RM		 = rm -fr
CFLAGS	= -Wall -Wextra -Werror
CC = gcc

all:		$(DIR_OBJ) ${NAME}

$(DIR_OBJ):
				@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c Makefile ./inc/libft.h
				@printf "\033[0;33m\r🔨 $< ✅ \033[0m"
				@$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
				@$(AR) $(NAME) $(OBJS)

clean:
				${RM} ${OBJS}

fclean:		clean
				${RM} ${NAME} ${DIR_OBJ}

re:			fclean all

.PHONY:		clean fclean re all
