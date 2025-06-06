/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validator.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 14:36:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 19:37:38 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	validate_map(t_map *map, t_player *player, t_animated_sprite_config *config)
{
	if (!map || !player)
		return (false);
	if (!validate_map_content(map, player, config))
		return (false);
	if (!validate_map_closure(map))
		return (false);
	return (true);
}

bool	validate_map_closure(t_map *map)
{
	if (!map || !map->grid)
		return (false);
	if (!check_map_borders(map))
		return (false);
	if (!check_surrounding_walls(map))
		return (false);
	if (!check_spaces_surrounded(map))
	{
		ft_putendl_fd("Error: Space has walkable area nearby", 2);
		return (false);
	}
	return (true);
}
