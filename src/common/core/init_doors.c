/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_doors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 17:11:16 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/17 11:07:40 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	init_single_door(t_map *map, int x, int y)
{
	if (!is_door(map, x, y))
	{
		ft_memset(&map->doors[y][x], 0, sizeof(t_door));
		map->doors[y][x].is_door = false;
		return ;
	}
	map->doors[y][x].mx = x;
	map->doors[y][x].my = y;
	map->doors[y][x].is_door = true;
	map->doors[y][x].state = DOOR_CLOSED;
	map->doors[y][x].openness = 0.0;
	if (map->grid[y - 1][x] == '1' && map->grid[y + 1][x] == '1')
		map->doors[y][x].type = DOOR_VERTICAL;
	else
		map->doors[y][x].type = DOOR_HORIZONTAL;
}

int	init_doors(t_map *map)
{
	int	i;
	int	width;
	int	j;

	if (!map)
		return (-1);
	if (!map->contains_door)
		return (0);
	map->doors = ft_calloc(map->height, sizeof(t_door *));
	if (!map->doors)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		width = ft_strlen(map->grid[i]);
		map->doors[i] = ft_calloc(width, sizeof(t_door));
		if (!map->doors[i])
			return (-1);
		j = 0;
		while (++j < width)
			init_single_door(map, j, i);
		i++;
	}
	return (0);
}
