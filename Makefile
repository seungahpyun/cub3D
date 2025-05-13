NAME = cub3D
CC = cc
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
SRC_DIR = src
PARSER_DIR = $(SRC_DIR)/parser
OBJ_DIR = obj
LIB_DIR = lib
MLX_DIR = MLX42
INCLUDE_DIR = include
SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/free_utils.c \
			$(PARSER_DIR)/check_map_closure.c \
			$(PARSER_DIR)/map_builder.c \
			$(PARSER_DIR)/parse_file.c \
			$(PARSER_DIR)/parse.c \
			$(PARSER_DIR)/parse_map.c \
			$(PARSER_DIR)/validation.c
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT = $(LIB_DIR)/libft.a
INCLUDES = -I $(INCLUDE_DIR) -I $(LIB_DIR)/include -I $(MLX_DIR)/include/MLX42

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(PARSER_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIB_DIR) --no-print-directory

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "\033[1;33mExecutable compiled!\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean  --no-print-directory
	@echo "\033[1;33mObject files cleaned!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean --no-print-directory
	@echo "\033[1;33mExecutable cleaned!\033[0m"

re: fclean all

.PHONY: all clean fclean re
