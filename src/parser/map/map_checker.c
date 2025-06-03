/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:16:48 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/03 15:25:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_map_chars(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] != '0' && map->grid[i][j] != '1'
				&& map->grid[i][j] != ' ' && map->grid[i][j] != 'N'
				&& map->grid[i][j] != 'S' && map->grid[i][j] != 'E'
				&& map->grid[i][j] != 'W' && map->grid[i][j] != 'T')
				return (0);
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S'
				|| map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
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
	{
		ft_putendl_fd("Error: Invalid characters in map", 2);
		return (false);
	}
	if (!find_player_position(map, player))
	{
		ft_putendl_fd("Error: Must have exactly one player position", 2);
		return (false);
	}
	parse_sprite_from_map(map);
	return (true);
}

bool	check_map_extension(const char *filename)
{
	return (check_file_extension(filename, ".cub"));
}
