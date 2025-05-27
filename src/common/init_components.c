/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_components.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 10:25:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/27 11:47:25 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->dir = '\0';
	player->angle = -1;
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
	map->width = 0;
	map->height = 0;
}
