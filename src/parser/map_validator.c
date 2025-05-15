/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validator.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 14:36:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 15:06:53 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_chars(char **map)
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

static bool	find_player_position(char **map, t_game *game)
{
	int	i;
	int	j;
	int	player_found;

	i = 0;
	player_found = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				game->player_x = j;
				game->player_y = i;
				game->player_dir = map[i][j];
				player_found++;
			}
			j++;
		}
		i++;
	}
	return (player_found == 1);
}

bool	validate_map_content(char **map, t_game *game)
{
	if (!map || !game)
		return (false);
	if (!check_map_chars(map))
	{
		ft_putendl_fd("Error: Invalid characters in map", 2);
		return (false);
	}
	if (!find_player_position(map, game))
	{
		ft_putendl_fd("Error: Must have exactly one player position", 2);
		return (false);
	}
	return (true);
}

bool	validate_map(t_game *game)
{
	if (!game || !game->map)
		return (false);
	if (!validate_map_content(game->map, game))
		return (false);
	if (!validate_map_closure(game))
		return (false);
	return (true);
}
