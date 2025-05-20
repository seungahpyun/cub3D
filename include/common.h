/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 14:33:47 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# define WIDTH 1920
# define HEIGHT 1080

# include <MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
}				t_map;

typedef struct s_player
{
	int			x;
	int			y;
	char		dir;
	double		angle;
}				t_player;

typedef struct s_minimap
{
	int			cell_size;
	mlx_image_t	*img;
}				t_minimap;

typedef struct s_game
{
	mlx_t		*mlx;
	t_asset		asset;
	t_map		map;
	t_player	player;
	t_minimap	minimap;
}				t_game;

/* error.c*/
void			ft_mlx_error(t_game *game);

/* free_utils.c */
void			free_map(t_map *map);
void			free_game(t_game *game);

/* init.c */
void			init_window(t_game *game);
void			init_game_state(t_game *game);

/* init_components.c */
void			init_player(t_player *player);
void			init_minimap(t_minimap *minimap);
void			init_map(t_map *map);

/* debug */
void			debug(t_game *game);

#endif
