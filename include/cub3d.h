/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:59:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/08 11:44:54 by spyun         ########   odam.nl         */
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
# include <stdbool.h>

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

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
	// t_player	player;
}	t_game;

/* main.c */
int		main(int argc, char **argv);

/* validation.c */
bool	check_file_extension(const char *filename);
bool	check_texture_path(const char *path);
bool	check_color_value(int r, int g, int b);
int		check_map_chars(char **map);

/* parse.c */
int		parse_texture_path(char *line, char **path);
int		parse_color_value(char *line, t_color *color);
int		parse_element(char *line, t_game *game);
int		parse_file(char *filename, t_game *game);

/* map_builder.c  */
t_list	*create_map_node(char *line);
int		add_first_line(t_list **map_lines, char *first_line);
int		build_map_array(t_game *game, t_list *map_lines);

/* parse_map.c */
int		get_map_width(char **map);
int		parse_map(int fd, t_game *game, char *line);

/* free_utils */
void	free_map(char **map, t_game *game);
void	free_game(t_game *game);

#endif
