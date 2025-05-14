/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_borders_validator.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 11:42:12 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/14 16:19:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_horizontal_borders(char **map, t_game *game)
{
	int	x;
	int	y;
	int	last_row;

	last_row = game->map_height - 1;
	y = 0;
	while (y <= last_row)
	{
		if (y == 0 || y == last_row)
		{
			x = 0;
			while (map[y][x])
			{
				if (map[y][x] != '1' && map[y][x] != ' ')
				{
					printf("Error: Map border not closed at (%d, %d)\n", x, y);
					return (false);
				}
				x++;
			}
		}
		y++;
	}
	return (true);
}

static bool	check_vertical_borders(char **map, t_game *game)
{
	int	x;
	int	y;
	int	last_row;

	last_row = game->map_height - 1;
	y = 0;
	while (y <= last_row)
	{
		x = 0;
		while (map[y][x])
		{
			if (x == 0 || x == (int)ft_strlen(map[y]) - 1)
			{
				if (map[y][x] != '1' && map[y][x] != ' ')
				{
					printf("Error: Map border not closed at (%d, %d)\n", x, y);
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
	if (!check_horizontal_borders(map->grid, map))
		return (false);
	if (!check_vertical_borders(map->grid, map))
		return (false);
	return (true);
}
