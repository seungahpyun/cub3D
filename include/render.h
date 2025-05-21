/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/21 15:26:43 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define MINIMAP_RADIUS 10
# define MINIMAP_CELL_SIZE 16
# define MINIMAP_W (MINIMAP_RADIUS * 2 + 1) * MINIMAP_CELL_SIZE
# define MINIMAP_H MINIMAP_W
# define MINIMAP_GRID (MINIMAP_RADIUS * 2 + 1)

# define MINIMAP_WALL_COLOR 0x003300FF   // dark green
# define MINIMAP_FLOOR_COLOR 0x006600FF  // brighter green
# define MINIMAP_PLAYER_COLOR 0xD1FFC7FF // light green
# define MINIMAP_EMPTY_COLOR 0x00000000
# define MINIMAP_RAY_COLOR 0x65965EFF

# define FOV 120.0

# include "common.h"

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_cell
{
	int	px;
	int	py;
	int	size;
	int	color;
}		t_cell;

/* utils */
int		is_within_boundary(int x, int y, int width, int height);
bool	is_valid_point(t_map *map, int mx, int my);
int		get_color(char c);
double	degree_to_radian(double degree);

void	setup_player_for_raycasting(t_player *player);

/* draw_primitives */
void	draw_line(mlx_image_t *img, t_point start, t_point end, int color);
void	draw_cell(mlx_image_t *img, t_cell cell);

/* cast_rays*/
// void	find_hit_point_horizon(t_map *map, t_player *player, t_ray *ray);

/* minimap_render*/
void	render_minimap(t_game *game);

/*test */
void	test_rays(t_game *game);

#endif
