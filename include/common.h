/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/10 15:15:02 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define WIDTH 1920
# define HEIGHT 1080
# define MAX_SPRITES 100
# define MIN_SPRITE_FRAMES 2
# define MAX_SPRITE_FRAMES 10

# define DOOR_SPEED 0.03

# include <MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_sprite_type
{
	SPRITE_ANIMATED = 'A'
}								t_sprite_type;

typedef struct s_sprite
{
	double						x;
	double						y;
	t_sprite_type				type;
	int							current_frame;
	double						last_frame_time;
	double						distance;
	int							frame_count;
	mlx_image_t					*frames[MAX_SPRITE_FRAMES];
}								t_sprite;

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}								t_door_state;

typedef enum e_door_type
{
	DOOR_VERTICAL,
	DOOR_HORIZONTAL
}								t_door_type;

typedef struct s_door
{
	bool						is_door;
	t_door_state				state;
	double						openness;
	t_door_type					type;
}								t_door;

typedef struct s_color
{
	int							r;
	int							g;
	int							b;
}								t_color;

typedef struct s_animated_sprite_config
{
	char						*paths[MAX_SPRITE_FRAMES];
	int							frame_count;
}								t_animated_sprite_config;

typedef struct s_asset
{
	char						*no_path;
	char						*so_path;
	char						*we_path;
	char						*ea_path;
	char						*door_path;
	t_color						floor;
	t_color						ceiling;
	mlx_image_t					*no_img;
	mlx_image_t					*so_img;
	mlx_image_t					*we_img;
	mlx_image_t					*ea_img;
	mlx_image_t					*door_img;
	t_animated_sprite_config	animated_sprite;
}								t_asset;

typedef struct s_map
{
	char						**grid;
	int							width;
	int							height;
	t_sprite					sprites[MAX_SPRITES];
	int							sprite_count;
	t_door						**doors;
}								t_map;

typedef struct s_player
{
	double						x;
	double						y;
	char						dir;
	double						angle;
}								t_player;

typedef struct s_minimap
{
	int							offset_x;
	int							offset_y;
	mlx_image_t					*img;
}								t_minimap;

typedef struct s_ray_data
{
	double						angle_offset;
	double						angle;
	double						dist;
	char						hit_side;
}								t_ray_data;

typedef struct s_game
{
	mlx_t						*mlx;
	mlx_image_t					*img;
	t_asset						asset;
	t_map						map;
	t_player					player;
	t_minimap					minimap;
	t_ray_data					rays[WIDTH];
}								t_game;

/* ========================================================================== */
/*                                    CORE                                    */
/* ========================================================================== */
/* error.c */
void							ft_mlx_error(t_game *game);
bool							print_error(const char *message,
									bool return_value);
bool							print_error_with_value(const char *prefix,
									const char *value, bool return_value);
/* init_components.c */
void							init_animated_sprite_in_asset(t_asset *asset);
void							init_sprite_frames(t_sprite *sprite);
void							init_player(t_player *player);
void							init_minimap(t_minimap *minimap);
void							init_map(t_map *map);
/* init.c */
void							init_window(t_game *game);
void							init_input_system(t_game *game);
void							init_game_state(t_game *game);
int								init_door_arrays(t_map *map);
/* ========================================================================== */
/*                                   MEMORY                                   */
/* ========================================================================== */
/* free_assets.c */
void							free_asset_images(t_asset *asset, mlx_t *mlx);
void							free_asset(t_asset *asset, mlx_t *mlx);
/* free_memory.c */
void							free_map(t_map *map);
void							free_game(t_game *game);
/* free_sprites.c */
void							free_all_sprites(t_game *game);
/* ========================================================================== */
/*                                   UTILS                                    */
/* ========================================================================== */
/* math_utils.c */
double							calculate_distance(double x1, double y1,
									double x2, double y2);
double							normalize_angle(double angle);
/* init_doors.c */
int								init_doors(t_map *map);

/* debug */
void							debug(t_game *game);
/* utils */
bool							is_within_boundary(int x, int y, int width,
									int height);
bool							is_valid_map_coord(t_map *map, int mx, int my);
bool							is_door(t_map *map, int x, int y);

#endif
