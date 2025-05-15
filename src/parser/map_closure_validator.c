/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_closure_validator.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 09:17:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 14:54:44 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_upper_row(char **map, int x, int y)
{
	if (x < (int)ft_strlen(map[y - 1]))
	{
		if (map[y - 1][x] == ' ' || (x > 0 && map[y - 1][x - 1] == ' ')
		|| (x < (int)ft_strlen(map[y - 1]) - 1 && map[y - 1][x + 1] == ' '))
			return (false);
	}
	else
		return (false);
	return (true);
}

static bool	check_lower_row(char **map, int x, int y)
{
	if (x < (int)ft_strlen(map[y + 1]))
	{
		if (map[y + 1][x] == ' ' || (x > 0 && map[y + 1][x - 1] == ' ')
		|| (x < (int)ft_strlen(map[y + 1]) - 1 && map[y + 1][x + 1] == ' '))
			return (false);
	}
	else
		return (false);
	return (true);
}

static bool	check_cell_surrounded(char **map, int x, int y, t_game *game)
{
	if (y == 0 || y == game->map_height - 1)
		return (false);
	if (x == 0 || x >= (int)ft_strlen(map[y]) - 1)
		return (false);
	if (!check_upper_row(map, x, y))
		return (false);
	if (!check_lower_row(map, x, y))
		return (false);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		return (false);
	return (true);
}

static bool	check_surrounding_walls(char **map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_walkable(map[y][x]))
			{
				if (!check_cell_surrounded(map, x, y, game))
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

bool	validate_map_closure(t_game *game)
{
	if (!game || !game->map)
		return (false);
	if (!check_map_borders(game->map, game))
		return (false);
	if (!check_surrounding_walls(game->map, game))
		return (false);
	if (!check_spaces_surrounded(game->map, game))
	{
		ft_putendl_fd("Error: Space has walkable area nearby", 2);
		return (false);
	}
	return (true);
}
