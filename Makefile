NAME = cub3D
CC = cc
SANITIZE   := -fsanitize=address
CFLAGS = -g3 $(SANITIZE) -Wall -Wextra -Werror
LDFLAGS := $(SANITIZE) -ldl -lglfw -pthread -lm

LIBMLX_DIR	:= ./lib/MLX42
LIBFT_DIR   := ./lib/libft

INCLUDE_DIR = include

SRC_DIR = src
PARSER_DIR = $(SRC_DIR)/parser
RENDER_DIR = $(SRC_DIR)/render
OBJ_DIR = obj

SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/free_utils.c \
			$(SRC_DIR)/error.c \
			$(PARSER_DIR)/element_validator.c \
			$(PARSER_DIR)/map_borders_validator.c \
			$(PARSER_DIR)/map_builder.c \
			$(PARSER_DIR)/map_closure_validator.c \
			$(PARSER_DIR)/map_spaces_validator.c \
			$(PARSER_DIR)/map_validator.c \
			$(PARSER_DIR)/parse_elements.c \
			$(PARSER_DIR)/parse_file.c \
			$(PARSER_DIR)/parse_map.c \
			$(RENDER_DIR)/minimap.c \
			$(RENDER_DIR)/render_utils.c \
			$(RENDER_DIR)/draw_primitives.c \


OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBMLX	= $(LIBMLX_DIR)/build/libmlx42.a
LIBFT   = $(LIBFT_DIR)/libft.a

INCLUDES = -I $(INCLUDE_DIR) -I $(LIBFT_DIR)/include -I $(LIBMLX_DIR)/include/MLX42

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(LIBMLX):
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4 --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_DIR) $(LIBFT) $(LIBMLX) $(OBJ_FILES)
	@$(CC) $(OBJ_FILES) $(LIBFT) $(LIBMLX) $(LDFLAGS) -o $(NAME)
	@echo "\033[1;33mExecutable compiled!\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(LIBMLX_DIR)/build
	@make -C $(LIBFT_DIR) clean  --no-print-directory
	@echo "\033[1;33mObject files cleaned!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "\033[1;33mExecutable cleaned!\033[0m"

re: fclean all

.PHONY: all clean fclean re
