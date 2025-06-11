/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 11:22:50 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/11 17:42:20 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	is_within_boundary(int x, int y, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (false);
	return (true);
}

bool	is_valid_map_coord(t_map *map, int mx, int my)
{
	if (!is_within_boundary(mx, my, map->height, map->width))
		return (false);
	if (mx >= (int)ft_strlen(map->grid[my]))
		return (false);
	return (true);
}

bool	is_door(t_map *map, int x, int y)
{
	if (!is_valid_map_coord(map, x, y))
		return (false);
	return (map->grid[y][x] == 'D');
}

bool	map_contains_door(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			if (is_valid_map_coord(map, x, y) && map->grid[y][x] == 'D')
				return (true);
			y++;
		}
		x++;
	}
	return (false);
}
