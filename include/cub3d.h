/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:59:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/16 16:53:01 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080

# define MINIMAP_RADIUS 10
# define MINIMAP_CELL_SIZE 16
# define MINIMAP_W (MINIMAP_RADIUS * 2 + 1) * MINIMAP_CELL_SIZE
# define MINIMAP_H MINIMAP_W
# define MINIMAP_GRID (MINIMAP_RADIUS * 2 + 1)
# define MINIMAP_WALL_COLOR 0x003300FF   // dark green
# define MINIMAP_FLOOR_COLOR 0x006600FF  // brighter green
# define MINIMAP_PLAYER_COLOR 0xD1FFC7FF // light green
# define MINIMAP_EMPTY_COLOR 0x00000000

# define NUM_RAYS 100
# define FOV 60

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

typedef struct s_cell
{
	int			px;
	int			py;
	int			size;
	int			color;
}				t_cell;

typedef struct s_line
{
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			color;
}				t_line;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*minimap;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	t_color		floor;
	t_color		ceiling;
	char		**map;
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_game;

/* main.c */
int				main(int argc, char **argv);

/* parser */
/* element_validator.c */
bool			check_map_extension(const char *filename);
bool			check_texture_path(const char *path);
bool			check_color_value(int r, int g, int b);
/* map_borders_validator.c */
bool			check_map_borders(char **map, t_game *game);
/* map_builder.c */
t_list			*create_map_node(char *line);
int				add_first_line(t_list **map_lines, char *first_line);
int				build_map_array(t_game *game, t_list *map_lines);
/* map_closure_validator.c */
bool			validate_map_closure(t_game *game);
/* map_spaces_validator.c */
bool			is_walkable(char c);
bool			check_spaces_surrounded(char **map, t_game *game);
/* map_validator.c */
int				check_map_chars(char **map);
bool			validate_map_content(char **map, t_game *game);
bool			validate_map(t_game *game);
/* parse_elements.c */
int				parse_element(char *line, t_game *game);
/* parse_file.c */
int				parse_file(char *filename, t_game *game);
/* parse_map.c */
int				parse_map(int fd, t_game *game, char *first_line);

/* render*/
bool			is_valid_point(t_game *game, int mx, int my);
void			render_minimap(t_game *game);

/* error.c*/
void			ft_mlx_error(t_game *game);

/* free_utils.c */
void			free_map(char **map, t_game *game);
void			free_game(t_game *game);

#endif
