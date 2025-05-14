/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:59:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/14 15:55:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080

# define MINI_TILE 8

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

typedef struct s_player
{
	int			x;
	int			y;
	char		dir;
}				t_player;

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

typedef struct s_minimap
{
	int			cell_size;
	mlx_image_t	*img;

}				t_minimap;

typedef struct s_game
{
	mlx_t		*mlx;
	t_minimap	minimap;
	t_asset		asset;
	t_player	player;
}				t_game;

/* main.c */
int				main(int argc, char **argv);

/* parser */
/* element_validator.c */
bool			check_map_extension(const char *filename);
bool			check_texture_path(const char *path);
bool			check_color_value(int r, int g, int b);
/* map_borders_validator.c */
bool			check_map_borders(char **map, t_map *map_data);
/* map_builder.c */
t_list			*create_map_node(char *line);
int				add_first_line(t_list **map_lines, char *first_line);
int				build_map_array(t_map *map_data, t_list *map_lines);
/* map_closure_validator.c */
bool			validate_map_closure(t_map *map_data, t_player *player);
/* map_spaces_validator.c */
bool			is_walkable(char c);
bool			check_spaces_surrounded(char **grid, t_map *map_data);
/* map_validator.c */
int				check_map_chars(char **grid);
bool			validate_map_content(char **grid, t_map *map_data, t_player *player);
bool			validate_map(t_map *map_data, t_player *player);
/* parse_elements.c */
int				parse_element(char *line, t_asset *asset);
/* parse_file.c */
int				parse_file(char *filename, t_game *game);
/* parse_map.c */
int				parse_map(int fd, t_game *game, char *first_line);

/* render*/
void			render_minimap(t_game *game);

/* error.c*/
void			ft_mlx_error(t_game *game);

/* free_utils.c */
void			free_map(char **map, t_game *game);
void			free_game(t_game *game);

#endif
