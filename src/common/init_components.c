/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_components.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 10:25:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/03 14:52:41 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	init_player(t_player *player)
{
	player->x = -1.0;
	player->y = -1.0;
	player->dir = '\0';
	player->angle = -1.0;
}

void	init_minimap(t_minimap *minimap)
{
	minimap->offset_x = 0;
	minimap->offset_y = 0;
	minimap->img = NULL;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->door_states = NULL;
	map->door_openness = NULL;
	map->width = 0;
	map->height = 0;
}
