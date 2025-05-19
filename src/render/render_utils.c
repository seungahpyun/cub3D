/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/19 09:48:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	is_within_map(int mx, int my, int map_width, int map_height)
{
	return (mx >= 0 && my >= 0 && mx < map_width && my < map_height);
}

bool	is_valid_point(t_game *game, int mx, int my)
{
	if (!is_within_map(mx, my, game->map.width, game->map.height))
		return (false);
	if (mx >= (int)ft_strlen(game->map.grid[my]))
		return (false);
	return (true);
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
