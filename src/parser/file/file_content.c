/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_content.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 14:58:06 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/17 11:43:02 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_map_content(t_game *game, int fd, int ret)
{
	bool	map_found;
	char	*line;

	map_found = false;
	line = get_next_line(fd);
	while (line != NULL && ret == 0)
	{
		ret = process_line(line, game, fd);
		if (ret == 1)
		{
			map_found = true;
			if (check_content_after_map(fd) == -1)
			{
				ret = -1;
				break ;
			}
		}
		if (ret == 0)
			line = get_next_line(fd);
	}
	if (ret != -1)
		ret = check_map_file(game, map_found);
	return (ret);
}

bool	map_contains_animated_sprites(t_map *map)
{
	int	i;

	if (!map || map->sprite_count <= 0)
		return (false);
	i = 0;
	while (i < map->sprite_count)
	{
		if (map->sprites[i].type == SPRITE_ANIMATED)
			return (true);
		i++;
	}
	return (false);
}

static bool	validate_map_consistency(t_asset *asset, t_map *map)
{
	map->contains_door = map_contains_door(map);
	if (map->contains_door && asset->door_path == NULL)
	{
		ft_putendl_fd("Error: Map contains doors but missing Door texture.", 2);
		return (false);
	}
	if (!map->contains_door && asset->door_path != NULL)
		ft_putendl_fd("Warning: Door texture specified but no doors in map", 2);
	if (map_contains_animated_sprites(map)
		&& !validate_animated_sprite_config(&asset->animated_sprite))
	{
		ft_putendl_fd("Error: Map contains animated sprites"
			" but missing or invalid ANIMATED configuration.", 2);
		return (false);
	}
	if (!map_contains_animated_sprites(map)
		&& asset->animated_sprite.frame_count > 0)
		ft_putendl_fd("Warning: ANIMATED configuration specified"
			" but no animated sprites in map", 2);
	return (true);
}

int	check_map_file(t_game *game, bool map_found)
{
	if (!check_all_elements_set(&game->asset))
		return (-1);
	if (!map_found)
	{
		ft_putendl_fd("Error: No map found in file", 2);
		return (-1);
	}
	if (!validate_map_consistency(&game->asset, &game->map))
		return (-1);
	return (0);
}
