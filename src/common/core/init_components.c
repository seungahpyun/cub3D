/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_components.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 10:25:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 19:42:09 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	init_animated_sprite_config(t_animated_sprite_config *config)
{
	int	i;

	if (!config)
		return ;
	config->frame_count = 0;
	i = 0;
	while (i < MAX_SPRITE_FRAMES)
	{
		config->paths[i] = NULL;
		i++;
	}
}

void	init_animated_sprite_in_asset(t_asset *asset)
{
	if (!asset)
		return ;
	init_animated_sprite_config(&asset->animated_sprite);
}

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
	map->door_states = NULL;
	map->door_openness = NULL;
	map->width = 0;
	map->height = 0;
	map->sprite_count = 0;
	i = 0;
	while (i < MAX_SPRITES)
	{
		map->sprites[i].x = -1.0;
		map->sprites[i].y = -1.0;
		map->sprites[i].type = SPRITE_ANIMATED;
		map->sprites[i].current_frame = 0;
		map->sprites[i].last_frame_time = 0.0;
		map->sprites[i].distance = 0.0;
		map->sprites[i].frame_count = 0;
		j = 0;
		while (j < MAX_SPRITE_FRAMES)
		{
			map->sprites[i].frames[j] = NULL;
			j++;
		}
		i++;
	}
}
