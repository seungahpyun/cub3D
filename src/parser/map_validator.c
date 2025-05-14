/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validator.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 14:36:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/14 16:47:42 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_map_chars(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ' &&
				map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' &&
				map[i][j] != 'W')
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' ||
				map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count == 1);
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
				player->x = j;
				player->y = i;
				player->dir = map->grid[i][j];
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
	{
		ft_putendl_fd("Error: Invalid characters in map", 2);
		return (false);
	}
	if (!find_player_position(map, player))
	{
		ft_putendl_fd("Error: Must have exactly one player position", 2);
		return (false);
	}
	return (true);
}

bool	validate_map(t_map *map, t_player *player)
{
	if (!map || !player)
		return (false);
	if (!validate_map_content(map, player))
		return (false);
	if (!validate_map_closure(map))
		return (false);
	return (true);
}
