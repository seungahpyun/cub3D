/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_closure_validator.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 09:17:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/14 16:33:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_upper_row(t_map *map, int x, int y)
{
	if (x < (int)ft_strlen(map->grid[y - 1]))
	{
		if (map->grid[y - 1][x] == ' ' || (x > 0 && map->grid[y - 1][x - 1] == ' ')
		|| (x < (int)ft_strlen(map->grid[y - 1]) - 1 && map->grid[y - 1][x + 1] == ' '))
			return (false);
	}
	else
		return (false);
	return (true);
}

static bool	check_lower_row(t_map *map, int x, int y)
{
	if (x < (int)ft_strlen(map->grid[y + 1]))
	{
		if (map->grid[y + 1][x] == ' ' || (x > 0 && map->grid[y + 1][x - 1] == ' ')
		|| (x < (int)ft_strlen(map->grid[y + 1]) - 1 && map->grid[y + 1][x + 1] == ' '))
			return (false);
	}
	else
		return (false);
	return (true);
}

static bool	check_cell_surrounded(t_map *map, int x, int y)
{
	if (y == 0 || y == map->height - 1)
		return (false);
	if (x == 0 || x >= (int)ft_strlen(map->grid[y]) - 1)
		return (false);
	if (!check_upper_row(map, x, y))
		return (false);
	if (!check_lower_row(map, x, y))
		return (false);
	if (map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
		return (false);
	return (true);
}

static bool	check_surrounding_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_walkable(map->grid[y][x]))
			{
				if (!check_cell_surrounded(map, x, y))
				{
					printf("Error: Map is not closed at (%d, %d)\n", x, y);
					return (false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map_closure(t_map *map)
{
	if (!map || !map->grid)
		return (false);
	if (!check_map_borders(map))
		return (false);
	if (!check_surrounding_walls(map))
		return (false);
	if (!check_spaces_surrounded(map))
	{
		ft_putendl_fd("Error: Space has walkable area nearby", 2);
		return (false);
	}
	return (true);
}
