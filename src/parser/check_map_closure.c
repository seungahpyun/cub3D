/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_closure.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 09:17:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 09:45:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_position(char **map, int x, int y, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (false);
	return (true);
}

bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}


bool	check_cell_surrounded(char **map, int x, int y, t_game *game)
{
	int width;
	int i;

	width = game->map_width;
	if (y == 0 || y == game->map_height -1)
		return (false);
	if (x == 0 || x >= (int)ft_strlen(map[y]) - 1)
		return (false);
	if (x < (int)ft_strlen(map[y - 1]))
	{
		if (map[y - 1][x] == ' ' || (x > 0 && map[y - 1][x - 1] == ' ') ||
			(x < (int)ft_strlen(map[y - 1]) - 1 && map[y - 1][x + 1] == ' '))
			return (false);
	}
	else
		return (false);
	if(x < (int)ft_strlen(map[y + 1]))
	{
		if (map[y + 1][x] == ' ' || (x > 0 && map[y + 1][x - 1] == ' ') ||
			(x < (int)ft_strlen(map[y + 1]) - 1 && map[y + 1][x + 1] == ' '))
			return (false);
	}
	else
		return (false);
	if (map[y][x-1] == ' ' || map[y][x + 1] == ' ')
		return (false);
	return (true);
}

bool	check_surrounding_walls(char **map, t_game *game)
{
	int x;
	int y;

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

				}
					return (false);
			}
			x++;
		}
	}
}

bool	check_borders(char **map, t_game *game)
{

}

bool	validate_map_closure(t_game *game);
