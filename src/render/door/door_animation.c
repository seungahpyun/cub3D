/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_animation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:04:17 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/06 17:04:22 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	handle_door_interaction(t_map *map, t_player *player,
		bool space_pressed)
{
	t_point	front;
	int		current_state;

	if (!space_pressed)
		return ;
	front.x = (int)(player->x + cos(player->angle) * 1.0);
	front.y = (int)(player->y - sin(player->angle) * 1.0);
	if (!is_door(map, front.x, front.y))
		return ;
	current_state = map->doors[front.y][front.x].state;
	if (current_state == DOOR_CLOSED)
		map->doors[front.y][front.x].state = DOOR_OPENING;
	else if (current_state == DOOR_OPEN)
		map->doors[front.y][front.x].state = DOOR_CLOSING;
	return ;
}

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

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (is_door(map, x, y))
				update_single_door(map, x, y, delta_time);
			y++;
		}
		x++;
	}
}
