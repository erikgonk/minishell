# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigonza <erigonza@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/26 16:38:02 by erigonza          #+#    #+#              #
#    Updated: 2024/07/22 12:24:32 by erigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS = 	main.c main_utils.c
SRCS_ENV = env_lst.c env_utils.c set_env.c
SRCS_PARSER = parser.c  parser_redir.c  parser_utils.c
SRCS_TOKENIZER = token_checks.c  tokenizer.c  token_utils.c
SRCS_SIGNALS = cmd_lst.c lex_lst.c signals.c

DIR_SRC = ./src
DIR_SRC_ENV = ./src/env
DIR_SRC_PARSER = ./src/parser
DIR_SRC_TOKENIZER = ./src/tokenizer
DIR_SRC_UTILS = ./src/utils

DIR_OBJ = $(DIR_SRC)/obj $(DIR_SRC_ENV)/obj $(DIR_SRC_PARSER)/obj $(DIR_SRC_TOKENIZER)/obj $(DIR_SRC_UTILS)/obj
OBJS = $(addprefix $(DIR_OBJ)/, $(SRCS:.c=.o))

LIB		= src/libft/libft.a

AR		= ar rcs

RM		 = rm -fr

INC = -I ./inc/tokenizer.h

CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

CC = gcc

all:		libft ${NAME}

libft: 
				make -C src/libft
				mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o:		$(DIR_SRC)/%.c Makefile ./inc/tokenizer.h
				$(CC) $(FLAGS) $(INC)  -c $< -o $@

${NAME}:	${OBJS}
				${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME} $(INC)

clean:
				make clean -C src/libft
				${RM} ${OBJS}

fclean:		clean
				make fclean -C src/libft 
				${RM} ${NAME} ${DIR_OBJ}

re:			fclean all

.PHONY:		clean fclean re all libft
.SILENT:
