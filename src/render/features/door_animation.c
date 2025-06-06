/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_animation.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 17:04:17 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/06 16:06:55 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	is_door(t_map *map, int x, int y)
{
	if (!is_valid_map_coord(map, x, y))
		return (false);
	return (map->grid[y][x] == 'D');
}

void	handle_door_interaction(t_map *map, t_player *player,
		bool space_pressed)
{
	t_point	front;
	int		current_state;

	if (!space_pressed)
		return ;
	front.x = (int)(player->x + cos(player->angle) * 1.0);
	front.y = (int)(player->y - sin(player->angle) * 1.0);
	current_state = map->door_states[front.y][front.x];
	if (!is_door(map, front.x, front.y))
		return ;
	if (current_state == DOOR_CLOSED)
		map->door_states[front.y][front.x] = DOOR_OPENING;
	else if (current_state == DOOR_OPEN)
		map->door_states[front.y][front.x] = DOOR_CLOSING;
	return ;
}

static void	update_single_door(t_map *map, int x, int y, double delta_time)
{
	if (map->door_states[y][x] == DOOR_OPENING)
	{
		map->door_openness[y][x] += DOOR_SPEED * delta_time;
		if (map->door_openness[y][x] >= 1.0)
		{
			map->door_openness[y][x] = 1.0;
			map->door_states[y][x] = DOOR_OPEN;
		}
	}
	else if (map->door_states[y][x] == DOOR_CLOSING)
	{
		map->door_openness[y][x] -= DOOR_SPEED * delta_time;
		if (map->door_openness[y][x] <= 0.0)
		{
			map->door_openness[y][x] = 0.0;
			map->door_states[y][x] = DOOR_CLOSED;
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
