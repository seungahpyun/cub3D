NAME = cub3d
CC = cc
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror
SRC_DIR = src
PARSER_DIR = $(SRC_DIR)/parser
OBJ_DIR = obj
LIB_DIR = lib
MLX_DIR = MLX42
INCLUDE_DIR = include
SRC_FILES = $(SRC_DIR)/main.c \
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
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean  --no-print-directory

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_DIR) fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re
