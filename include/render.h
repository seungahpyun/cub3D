/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/27 17:00:22 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define MINIMAP_RADIUS 10
# define MINIMAP_CELL_SIZE 50
# define MINIMAP_W (MINIMAP_RADIUS * 2 + 1) * MINIMAP_CELL_SIZE
# define MINIMAP_H MINIMAP_W
# define MINIMAP_GRID (MINIMAP_RADIUS * 2 + 1)

# define MINIMAP_WALL_COLOR 0xFFAA96B2
# define MINIMAP_FLOOR_COLOR 0xFFEFE7D3
# define MINIMAP_PLAYER_COLOR 0xD1FFC7FF // light green
# define MINIMAP_EMPTY_COLOR 0x00000000
# define MINIMAP_RAY_COLOR 0x65965EFF

# define RED 0xFF0000FF

# define FOV 60.0
# define MIN_PER_DIST 0.0001

# include "common.h"

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_cell
{
	int		px;
	int		py;
	int		size;
	int		color;
}			t_cell;

typedef struct s_ray
{
	double	start_x;
	double	start_y;
	int		map_x;
	int		map_y;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	dist_inc_x;
	double	dist_inc_y;
	int		step_x;
	int		step_y;
	double	dist_to_v;
	double	dist_to_h;
	char	hit_side;
}			t_ray;

/* utils */
int			is_within_boundary(int x, int y, int width, int height);
bool		is_valid_point(t_map *map, int mx, int my);
int			get_color(char c);
double		degree_to_radian(double degree);
int			color_to_rgba(t_color *color, int a);

/*render*/
void		render(t_game *game);
void		setup_for_raycasting(t_game *game);

/* draw_primitives */
void		draw_line(mlx_image_t *img, t_point start, t_point end, int color);
void		draw_cell(mlx_image_t *img, t_cell cell);

/* cast_rays*/
void		init_ray(t_player *player, double ray_angle, t_ray *ray);
double		cast_ray(t_map *map, t_ray *ray);

/* minimap_render*/
void		render_minimap(t_game *game);
void		render_3d_projection(t_game *game);

#endif
