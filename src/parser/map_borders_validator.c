/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_borders_validator.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 11:42:12 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 09:48:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	check_horizontal_borders(t_map *map)
{
	int	x;
	int	y;
	int	last_row;

	last_row = map->height - 1;
	y = 0;
	while (y <= last_row)
	{
		if (y == 0 || y == last_row)
		{
			x = 0;
			while (map->grid[y][x])
			{
				if (map->grid[y][x] != '1' && map->grid[y][x] != ' ')
				{
					printf("Error: Map border not closed at (%d, %d)\n", y, x);
					return (false);
				}
				x++;
			}
		}
		y++;
	}
	return (true);
}

static bool	check_vertical_borders(t_map *map)
{
	int	x;
	int	y;
	int	last_row;

	last_row = map->height - 1;
	y = 0;
	while (y <= last_row)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (x == 0 || x == (int)ft_strlen(map->grid[y]) - 1)
			{
				if (map->grid[y][x] != '1' && map->grid[y][x] != ' ')
				{
					printf("Error: Map border not closed at (%d, %d)\n", y, x);
					return (false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_map_borders(t_map *map)
{
	if (!check_horizontal_borders(map))
		return (false);
	if (!check_vertical_borders(map))
		return (false);
	return (true);
}
