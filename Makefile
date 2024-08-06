# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./inc -I./src/libft/inc -I/opt/homebrew/opt/readline/include

# Directories
SRC_DIR = ./src
OBJ_DIR = ./obj
LIBFT_DIR = ./src/libft
INC = ./inc/*.h

# Source files
SRC_FILES = $(SRC_DIR)/main.c \
            $(SRC_DIR)/main_utils.c \
            $(SRC_DIR)/env/env_lst.c \
            $(SRC_DIR)/env/set_env.c \
            $(SRC_DIR)/expand/expand.c \
            $(SRC_DIR)/expand/status_utils.c \
            $(SRC_DIR)/expand/var_expand.c \
            $(SRC_DIR)/parser/parser.c \
            $(SRC_DIR)/parser/parser_redir.c \
            $(SRC_DIR)/parser/parser_utils.c \
            $(SRC_DIR)/tokenizer/token_checks.c \
            $(SRC_DIR)/tokenizer/token_utils.c \
            $(SRC_DIR)/tokenizer/tokenizer.c \
            $(SRC_DIR)/utils/cmd_lst.c \
            $(SRC_DIR)/utils/input_checks.c \
            $(SRC_DIR)/utils/lex_lst.c \

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = minishell

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline -lhistory -L/opt/homebrew/opt/readline/lib

# Makefile rules
all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(LIBFT) $(INC)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re