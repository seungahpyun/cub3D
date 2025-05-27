/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_player.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/23 17:00:58 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/27 16:17:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	calculate_player_screen_pos(t_game *game, t_point *pos)
{
	double	player_screen_x;
	double	player_screen_y;

	player_screen_x = (game->player.x
			- ((int)game->player.x - MINIMAP_RADIUS)) * MINIMAP_CELL_SIZE;
	player_screen_y = (game->player.y
			- ((int)game->player.y - MINIMAP_RADIUS)) * MINIMAP_CELL_SIZE;
	pos->x = (int)player_screen_x;
	pos->y = (int)player_screen_y;
}

void	draw_minimap_player(t_game *game)
{
	t_cell	player_cell;
	t_point	pos;

	calculate_player_screen_pos(game, &pos);
	player_cell.px = pos.x - (MINIMAP_CELL_SIZE * 3 / 4) / 2;
	player_cell.py = pos.y - (MINIMAP_CELL_SIZE * 3 / 4) / 2;
	player_cell.size = MINIMAP_CELL_SIZE * 3 / 4;
	player_cell.color = MINIMAP_PLAYER_COLOR;
	draw_cell(game->minimap.img, player_cell);
}
