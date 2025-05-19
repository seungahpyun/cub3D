/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/19 17:42:17 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	is_within_boundary(int mx, int my, int width, int height)
{
	return (mx >= 0 && my >= 0 && mx < width && my < height);
}

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

double	dir_to_angle(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'W')
		return (M_PI);
	if (c == 'S')
		return (3 * M_PI / 2);
	return (-1);
}

bool	is_valid_point(t_game *game, int mx, int my)
{
	if (!is_within_boundary(mx, my, game->map_width, game->map_height))
		return (false);
	if (mx >= (int)ft_strlen(game->map.grid[my]))
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
