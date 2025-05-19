/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_spaces_validator.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 11:43:41 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 09:48:20 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	is_valid_position(int x, int y, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (false);
	return (true);
}

static bool	check_space_adjacents(t_map *map, int x, int y)
{
	if (is_valid_position(x + 1, y, map->height, map->width)
		&& map->grid[y][x + 1] && is_walkable(map->grid[y][x + 1]))
		return (false);
	if (is_valid_position(x - 1, y, map->height, map->width)
		&& x > 0 && is_walkable(map->grid[y][x - 1]))
		return (false);
	if (is_valid_position(x, y + 1, map->height, map->width)
		&& map->grid[y + 1] && x < (int)ft_strlen(map->grid[y + 1])
		&& is_walkable(map->grid[y + 1][x]))
		return (false);
	if (is_valid_position(x, y - 1, map->height, map->width)
		&& y > 0 && x < (int)ft_strlen(map->grid[y - 1])
		&& is_walkable(map->grid[y - 1][x]))
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
