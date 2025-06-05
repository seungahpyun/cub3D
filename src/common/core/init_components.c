/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_components.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 10:25:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:23:48 by spyun         ########   odam.nl         */
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
	int	i;
	int	j;

	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->sprite_count = 0;
	i = 0;
	while (i < MAX_SPRITES)
	{
		map->sprites[i].x = -1.0;
		map->sprites[i].y = -1.0;
		map->sprites[i].type = SPRITE_TREE;
		map->sprites[i].current_frame = 0;
		map->sprites[i].last_frame_time = 0.0;
		map->sprites[i].distance = 0.0;
		j = 0;
		while (j < TREE_FRAMES)
		{
			map->sprites[i].frames[j] = NULL;
			j++;
		}
		i++;
	}
}
