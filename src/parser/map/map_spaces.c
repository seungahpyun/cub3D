/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_spaces.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 11:43:41 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 19:10:57 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	check_space_adjacents(t_map *map, int x, int y)
{
	if (is_within_boundary(x + 1, y, map->height, map->width) && map->grid[y][x
		+ 1] && is_walkable(map->grid[y][x + 1]))
		return (false);
	if (is_within_boundary(x - 1, y, map->height, map->width) && x > 0
		&& is_walkable(map->grid[y][x - 1]))
		return (false);
	if (is_within_boundary(x, y + 1, map->height, map->width) && map->grid[y
			+ 1] && x < (int)ft_strlen(map->grid[y + 1])
		&& is_walkable(map->grid[y + 1][x]))
		return (false);
	if (is_within_boundary(x, y - 1, map->height, map->width) && y > 0
		&& x < (int)ft_strlen(map->grid[y - 1]) && is_walkable(map->grid[y
				- 1][x]))
		return (false);
	return (true);
}

bool	check_spaces_surrounded(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == ' ')
			{
				if (!check_space_adjacents(map, x, y))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
