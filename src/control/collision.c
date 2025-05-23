/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 09:04:17 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/23 15:09:58 by spyun         ########   odam.nl         */
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
