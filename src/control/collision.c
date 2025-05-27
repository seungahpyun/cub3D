/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 09:04:17 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/27 11:47:20 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

bool	can_move_to(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_y < 0 || map_y >= game->map.height)
		return (false);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (false);
	if (game->map.grid[map_y][map_x] == '1')
		return (false);
	if (game->map.grid[map_y][map_x] == ' ')
		return (false);
	return (true);
}

bool	can_move_x(t_game *game, double new_x)
{
	return (can_move_to(game, new_x, game->player.y));
}

bool	can_move_y(t_game *game, double new_y)
{
	return (can_move_to(game, game->player.x, new_y));
}

void	apply_sliding_movement(t_game *game, double new_x, double new_y)
{
	bool	can_move_both;
	bool	can_move_x_only;
	bool	can_move_y_only;

	can_move_both = can_move_to(game, new_x, new_y);
	can_move_x_only = can_move_x(game, new_x);
	can_move_y_only = can_move_y(game, new_y);
	if (can_move_both)
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	else if (can_move_x_only)
		game->player.x = new_x;
	else if (can_move_y_only)
		game->player.y = new_y;
}
