/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:59:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 10:49:17 by spyun         ########   odam.nl         */
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

// typedef struct s_player
// {
// 	double	x;
// 	double	y;
// 	double	dir_x;
// 	double	dir_y;
// 	double	plane_x;
// 	double	plane_y;
// 	double	move_speed;
// 	double	rot_speed;
// }	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	void		*win;
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
	// t_player	player;
}				t_game;

/* main.c */
int				main(int argc, char **argv);

/* validation.c */
bool			check_map_extension(const char *filename);
bool			check_texture_path(const char *path);
bool			check_color_value(int r, int g, int b);
int				check_map_chars(char **map);

/* check_map_closure.c */
bool	validate_map_closure(t_game *game);

/* parse.c */
int				parse_texture_path(char *line, char **path);
int				parse_color_value(char *line, t_color *color);
int				parse_element(char *line, t_game *game);
int				parse_file(char *filename, t_game *game);

/* map_builder.c  */
t_list			*create_map_node(char *line);
int				add_first_line(t_list **map_lines, char *first_line);
int				build_map_array(t_game *game, t_list *map_lines);

/* parse_map.c */
int				get_map_width(char **map);
int				parse_map(int fd, t_game *game, char *line);

/* render*/
void			render_minimap(t_game *game);

/* error*/
void			ft_mlx_error(t_game *game);

/* free_utils */
void			free_map(char **map, t_game *game);
void			free_game(t_game *game);

#endif
