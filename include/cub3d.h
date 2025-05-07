/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:59:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/07 12:31:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <libft.h>
# include "MLX42.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
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
	t_player	player;
}	t_game;

int		main(int argc, char **argv);

bool	check_file_extension(const char *filename);
bool	check_texture_path(const char *path);
bool	check_color_value(int r, int g, int b);
int		check_map_chars(char **map);

int		parse_texture_path(char *line, char **path);
int		parse_color_value(char *line, t_color *color);
int		parse_element(char *line, t_game *game);
int		parse_file(char *filename, t_game *game);

int		parse_map(int fd, t_game *game, char *line);

void	free_map(char **map, t_game *game);
void	free_game(t_game *game);

#endif
