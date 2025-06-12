/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_animation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:04:17 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/12 10:40:44 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	update_single_door(t_map *map, int x, int y, double delta_time)
{
	if (map->doors[y][x].state == DOOR_OPENING)
	{
		map->doors[y][x].openness += DOOR_SPEED * delta_time;
		if (map->doors[y][x].openness >= 1.0)
		{
			map->doors[y][x].openness = 1.0;
			map->doors[y][x].state = DOOR_OPEN;
		}
	}
	else if (map->doors[y][x].state == DOOR_CLOSING)
	{
		map->doors[y][x].openness -= DOOR_SPEED * delta_time;
		if (map->doors[y][x].openness <= 0.0)
		{
			map->doors[y][x].openness = 0.0;
			map->doors[y][x].state = DOOR_CLOSED;
		}
	}
}

void	update_doors(t_map *map, double delta_time)
{
	int	x;
	int	y;
	int	width;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		width = ft_strlen(map->grid[y]);
		while (x < width)
		{
			if (map->doors[y][x].is_door)
				update_single_door(map, x, y, delta_time);
			x++;
		}
		y++;
	}
}
