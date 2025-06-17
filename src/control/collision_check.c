/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 09:04:17 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/10 15:18:27 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

static bool	check_sprite_collision(t_game *game, double x, double y)
{
	int		i;
	double	distance;

	i = 0;
	while (i < game->map.sprite_count)
	{
		distance = calculate_distance(x, y, game->map.sprites[i].x,
				game->map.sprites[i].y);
		if (distance < 0.4)
			return (true);
		i++;
	}
	return (false);
}

static bool	is_walkable_cell(t_game *game, int map_x, int map_y)
{
	if (!is_valid_map_coord(&game->map, map_x, map_y))
		return (false);
	if (game->map.grid[map_y][map_x] == '1')
		return (false);
	if (game->map.grid[map_y][map_x] == ' ')
		return (false);
	if (game->map.grid[map_y][map_x] == 'D')
	{
		if (game->map.doors[map_y][map_x].state != DOOR_OPEN)
			return (false);
	}
	return (true);
}

bool	can_move_to(t_game *game, double new_x, double new_y)
{
	int	left_x;
	int	right_x;
	int	top_y;
	int	bottom_y;

	if (check_sprite_collision(game, new_x, new_y))
		return (false);
	left_x = (int)(new_x - 0.2);
	right_x = (int)(new_x + 0.2);
	top_y = (int)(new_y - 0.2);
	bottom_y = (int)(new_y + 0.2);
	if (!is_walkable_cell(game, left_x, top_y))
		return (false);
	if (!is_walkable_cell(game, right_x, top_y))
		return (false);
	if (!is_walkable_cell(game, left_x, bottom_y))
		return (false);
	if (!is_walkable_cell(game, right_x, bottom_y))
		return (false);
	return (true);
}
