/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_closure.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 09:17:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 10:40:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_position(int x, int y, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (false);
	return (true);
}

static bool	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}


static bool	check_cell_surrounded(char **map, int x, int y, t_game *game)
{
	int	width;

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

static bool	check_map_borders(char **map, t_game *game)
{
	int	x;
	int	y;
	int	last_row;

	last_row = game->map_height - 1;
	y = 0;
	while(y <= last_row)
	{
		if (y == 0 || y == last_row)
		{
			x = 0;
			while (map[y][x])
			{
				if (map[y][x] != '1' && map[y][x] != ' ')
				{
					ft_putendl_fd("Error: Map border not closed", 2);
					return (false);
				}
				x++;
			}
		}
		y++;
	}
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
					ft_putendl_fd("Error: Map border not closed", 2);
					return (false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}

static bool	check_spaces_surrounded(char **map, t_game *game)
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
				if (is_valid_position(x + 1, y, game->map_height, game->map_width) &&
					map[y][x + 1] && is_walkable(map[y][x + 1]))
					return (false);
				if (is_valid_position(x - 1, y, game->map_height, game->map_width) &&
					x > 0 && is_walkable(map[y][x - 1]))
					return (false);
				if (is_valid_position(x, y + 1, game->map_height, game->map_width) &&
					map[y + 1] && x < (int)ft_strlen(map[y + 1]) && is_walkable(map[y + 1][x]))
					return (false);
				if (is_valid_position(x, y - 1, game->map_height, game->map_width) &&
					y > 0 && x < (int)ft_strlen(map[y - 1]) && is_walkable(map[y - 1][x]))
					return (false);
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
