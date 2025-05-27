/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/23 15:13:21 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	color_to_rgba(t_color *color, int a)
{
	return (color->r << 24 | color->g << 16 | color->b << 8 | a);
}

int	is_within_boundary(int x, int y, int width, int height)
{
	return (x >= 0 && y >= 0 && x < width && y < height);
}

double	degree_to_radian(double degree)
{
	if (degree < 0)
		degree += 360;
	return (degree * M_PI / 180);
}

bool	is_valid_point(t_map *map, int mx, int my)
{
	if (!is_within_boundary(mx, my, map->width, map->height))
		return (false);
	if (mx >= (int)ft_strlen(map->grid[my]))
		return (false);
	return (true);
}

int	get_color(char c)
{
	if (c == '1')
		return (MINIMAP_WALL_COLOR);
	if (c == '0')
		return (MINIMAP_FLOOR_COLOR);
	if (c == ' ')
		return (MINIMAP_EMPTY_COLOR);
	return (MINIMAP_PLAYER_COLOR);
}

// int	calculate_cell_size(int map_width, int map_height)
// {
// 	float	cell_w;
// 	float	cell_h;
// 	int		cell_size;

// 	cell_w = (float)MINIMAP_W / map_width;
// 	cell_h = (float)MINIMAP_H / map_height;
// 	cell_size = (int)fminf(cell_w, cell_h);
// 	if (cell_size < 1)
// 		cell_size = 1;
// 	return (cell_size);
// }

// static void	draw_player(t_game *game)
// {
// 	int	player_px;
// 	int	player_py;
// 	int	cell_size;
// 	int	player_size;

// 	cell_size = game->minimap.cell_size;
// 	player_size = cell_size / 3;
// 	if (player_size < 1)
// 		player_size = 1;
// 	player_px = game->player_x * cell_size + player_size;
// 	player_py = game->player_y * cell_size + player_size;
// 	draw_cell(game->minimap.img, player_px, player_py, player_size,
// 		MINIMAP_PLAYER_COLOR);
// }
