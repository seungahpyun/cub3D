/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:16:48 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/04 12:51:52 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Check the door positon is valid or not:
 * 1. Check if the door is on the edge
 * 2. If door is vertical:
 * 		- Check walls above/below, walkable space left/right
 *    If door is horizontal:
 * 		- Check walls left/right, walkable space above/below
 * 3. Otherwise return false
 */
static bool	is_valid_door(t_map *map, int x, int y)
{
	if (x == 0 || y == 0 || x >= (int)ft_strlen(map->grid[y]) - 1
		|| y >= map->height - 1)
		return (false);
	if (is_valid_map_coord(map, x, y - 1) && is_valid_map_coord(map, x, y + 1)
		&& is_valid_map_coord(map, x - 1, y) && is_valid_map_coord(map, x + 1,
			y))
	{
		if (map->grid[y - 1][x] == '1' && map->grid[y + 1][x] == '1')
			return (is_walkable(map->grid[y][x - 1])
				&& is_walkable(map->grid[y][x + 1]));
		if (map->grid[y][x - 1] == '1' && map->grid[y][x + 1] == '1')
			return (is_walkable(map->grid[y - 1][x]) && is_walkable(map->grid[y
					+ 1][x]));
	}
	return (false);
}

static bool	check_map_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (!is_map_char(map->grid[i][j]))
				return (ft_putendl_fd("Error: Invalid characters in map", 2),
					false);
			if (map->grid[i][j] == 'D')
			{
				if (!is_valid_door(map, j, i))
					return (ft_putendl_fd("Error: Invalid door in map", 2),
						false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static bool	find_player_position(t_map *map, t_player *player)
{
	int	i;
	int	j;
	int	player_found;

	i = 0;
	player_found = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				player->x = j + 0.5;
				player->y = i + 0.5;
				player->dir = map->grid[i][j];
				map->grid[i][j] = '0';
				player_found++;
			}
			j++;
		}
		i++;
	}
	return (player_found == 1);
}

bool	validate_map_content(t_map *map, t_player *player)
{
	if (!map || !player)
		return (false);
	if (!check_map_chars(map))
		return (false);
	if (!find_player_position(map, player))
	{
		ft_putendl_fd("Error: Must have exactly one player position", 2);
		return (false);
	}
	return (true);
}

bool	check_map_extension(const char *filename)
{
	return (check_file_extension(filename, ".cub"));
}
