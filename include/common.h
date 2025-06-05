/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 14:34:42 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define WIDTH 1920
# define HEIGHT 1080
# define MAX_SPRITES 100
# define TREE_FRAMES 6

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
	SPRITE_TREE = 'T'
}				t_sprite_type;

typedef struct s_sprite
{
	double			x;
	double			y;
	t_sprite_type	type;
	int				current_frame;
	double			last_frame_time;
	double			distance;
	mlx_image_t		*frames[TREE_FRAMES];
}					t_sprite;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef struct s_asset
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_color		floor;
	t_color		ceiling;
	mlx_image_t	*no_img;
	mlx_image_t	*so_img;
	mlx_image_t	*we_img;
	mlx_image_t	*ea_img;
}				t_asset;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_sprite	sprites[MAX_SPRITES];
	int			sprite_count;
}				t_map;

typedef struct s_player
{
	double		x;
	double		y;
	char		dir;
	double		angle;
}				t_player;

typedef struct s_minimap
{
	int			offset_x;
	int			offset_y;
	mlx_image_t	*img;
}				t_minimap;

typedef struct s_ray_data
{
	double		angle_offset;
	double		angle;
	double		dist;
	char		hit_side;
}				t_ray_data;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_asset		asset;
	t_map		map;
	t_player	player;
	t_minimap	minimap;
	t_ray_data	rays[WIDTH];
}				t_game;

/* error.c */
void			ft_mlx_error(t_game *game);
bool			print_error(const char *message, bool return_value);
bool			print_error_with_value(const char *prefix, const char *value,
					bool return_value);

/* free_assets.c */
void			free_asset_images(t_asset *asset, mlx_t *mlx);
void			free_asset(t_asset *asset, mlx_t *mlx);

/* free_memory.c */
void			free_map(t_map *map);
void			free_game(t_game *game);

/* free_sprites.c */
void			free_all_sprites(t_game *game);

/* init.c */
void			init_window(t_game *game);
void			init_input_system(t_game *game);
void			init_game_state(t_game *game);

/* init_components.c */
void			init_player(t_player *player);
void			init_minimap(t_minimap *minimap);
void			init_map(t_map *map);

/* debug */
void			debug(t_game *game);

/* math_utils.c */
double	calculate_distance(double x1, double y1, double x2, double y2);
double	normalize_angle(double angle);
#endif
