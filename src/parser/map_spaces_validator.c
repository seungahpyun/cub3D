/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_spaces_validator.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 11:43:41 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 14:55:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static bool	check_space_adjacents(char **map, int x, int y, t_game *game)
{
	if (is_valid_position(x + 1, y, game->map_height, game->map_width)
		&& map[y][x + 1] && is_walkable(map[y][x + 1]))
		return (false);
	if (is_valid_position(x - 1, y, game->map_height, game->map_width)
		&& x > 0 && is_walkable(map[y][x - 1]))
		return (false);
	if (is_valid_position(x, y + 1, game->map_height, game->map_width)
		&& map[y + 1] && x < (int)ft_strlen(map[y + 1])
		&& is_walkable(map[y + 1][x]))
		return (false);
	if (is_valid_position(x, y - 1, game->map_height, game->map_width)
		&& y > 0 && x < (int)ft_strlen(map[y - 1])
		&& is_walkable(map[y - 1][x]))
		return (false);
	return (true);
}

bool	check_spaces_surrounded(char **map, t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == ' ')
			{
				if (!check_space_adjacents(map, x, y, game))
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}
