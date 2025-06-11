NAME = cub3D
CC = cc
SANITIZE   := -fsanitize=address
CFLAGS = -g3 $(SANITIZE) -Wall -Wextra -Werror
LDFLAGS := $(SANITIZE) -ldl -lglfw -pthread -lm
LDFLAGS += -L/opt/homebrew/lib

LIBMLX_DIR	:= ./lib/MLX42
LIBFT_DIR   := ./lib/libft

INCLUDE_DIR = include

SRC_DIR = src

COMMON_DIR = $(SRC_DIR)/common
COMMON_CORE_DIR += $(COMMON_DIR)/core
COMMON_MEMORY_DIR += $(COMMON_DIR)/memory
COMMON_UTILS_DIR += $(COMMON_DIR)/utils

CONTROL_DIR = $(SRC_DIR)/control

PARSER_DIR = $(SRC_DIR)/parser
PARSER_ELEMENT_DIR = $(PARSER_DIR)/element
PARSER_FILE_DIR = $(PARSER_DIR)/file
PARSER_MAP_DIR = $(PARSER_DIR)/map
PARSER_UTILS_DIR = $(PARSER_DIR)/utils

RENDER_DIR = $(SRC_DIR)/render
RENDER_CORE_DIR = $(RENDER_DIR)/core
RENDER_DOOR_DIR = $(RENDER_DIR)/door
RENDER_MINIMAP_DIR = $(RENDER_DIR)/minimap
RENDER_SPRITE_DIR = $(RENDER_DIR)/sprite
RENDER_TEXTURE_DIR = $(RENDER_DIR)/texture
RENDER_UTILS_DIR = $(RENDER_DIR)/utils

OBJ_DIR = obj

SRC_FILES = $(SRC_DIR)/main.c \
			\
			$(COMMON_DIR)/debug.c \
			$(COMMON_CORE_DIR)/error.c \
			$(COMMON_CORE_DIR)/init_components.c \
			$(COMMON_CORE_DIR)/init_doors.c \
			$(COMMON_CORE_DIR)/init_player_minimap.c \
			$(COMMON_CORE_DIR)/init.c \
			$(COMMON_MEMORY_DIR)/free_assets.c \
			$(COMMON_MEMORY_DIR)/free_memory.c \
			$(COMMON_MEMORY_DIR)/free_sprites.c \
			\
			$(COMMON_UTILS_DIR)/utils.c \
			$(COMMON_UTILS_DIR)/math_utils.c \
			\
			$(CONTROL_DIR)/collision_check.c \
			$(CONTROL_DIR)/collision_movement.c \
			$(CONTROL_DIR)/keyboard_input.c \
			$(CONTROL_DIR)/mouse_input.c \
			$(CONTROL_DIR)/player_controller.c \
			\
			$(PARSER_ELEMENT_DIR)/animated_sprite_parser.c \
			$(PARSER_ELEMENT_DIR)/color_component_parser.c \
			$(PARSER_ELEMENT_DIR)/color_parser.c \
			$(PARSER_ELEMENT_DIR)/element_checker.c \
			$(PARSER_ELEMENT_DIR)/element_parser.c \
			$(PARSER_ELEMENT_DIR)/sprite_parser.c \
			$(PARSER_ELEMENT_DIR)/texture_parser.c \
			\
			$(PARSER_FILE_DIR)/file_content.c \
			$(PARSER_FILE_DIR)/file_parser.c \
			$(PARSER_FILE_DIR)/file_processor.c \
			\
			$(PARSER_MAP_DIR)/map_borders.c \
			$(PARSER_MAP_DIR)/map_builder.c \
			$(PARSER_MAP_DIR)/map_checker.c \
			$(PARSER_MAP_DIR)/map_closure.c \
			$(PARSER_MAP_DIR)/map_loader.c \
			$(PARSER_MAP_DIR)/map_spaces.c \
			$(PARSER_MAP_DIR)/map_validator.c \
			\
			$(PARSER_UTILS_DIR)/file_utils.c \
			$(PARSER_UTILS_DIR)/map_utils.c \
			$(PARSER_UTILS_DIR)/sprite_utils.c \
			$(PARSER_UTILS_DIR)/string_utils.c \
			\
			$(RENDER_CORE_DIR)/cast_rays.c \
			$(RENDER_CORE_DIR)/projection_3d.c \
			$(RENDER_CORE_DIR)/projection_draw.c \
			$(RENDER_CORE_DIR)/render.c \
			$(RENDER_CORE_DIR)/setup.c \
			\
			$(RENDER_MINIMAP_DIR)/minimap_grid.c \
			$(RENDER_MINIMAP_DIR)/minimap_player.c \
			$(RENDER_MINIMAP_DIR)/minimap.c \
			\
			$(RENDER_SPRITE_DIR)/sprite_animation.c \
			$(RENDER_SPRITE_DIR)/sprite_drawing.c \
			$(RENDER_SPRITE_DIR)/sprite_loader.c \
			$(RENDER_SPRITE_DIR)/sprite_position.c \
			$(RENDER_SPRITE_DIR)/sprite_renderer.c\
			$(RENDER_SPRITE_DIR)/sprite_sorting.c \
			\
			$(RENDER_TEXTURE_DIR)/texture_loader.c \
			$(RENDER_TEXTURE_DIR)/texture_pixel.c \
			$(RENDER_TEXTURE_DIR)/texture_renderer.c\
			\
			$(RENDER_UTILS_DIR)/draw_primitives.c \
			$(RENDER_UTILS_DIR)/pixel_utils.c \
			$(RENDER_UTILS_DIR)/render_utils.c \
			\
			$(RENDER_DOOR_DIR)/door_animation.c \
			$(RENDER_DOOR_DIR)/door_render.c \
			$(RENDER_DOOR_DIR)/door_cast_ray.c \


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
