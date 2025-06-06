/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_components.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 10:25:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 20:10:37 by seungah       ########   odam.nl         */
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

static void	init_sprite_frames(t_sprite *sprite)
{
	int	j;

	j = 0;
	while (j < MAX_SPRITE_FRAMES)
	{
		sprite->frames[j] = NULL;
		j++;
	}
}

static void	init_single_sprite(t_sprite *sprite)
{
	sprite->x = -1.0;
	sprite->y = -1.0;
	sprite->type = SPRITE_ANIMATED;
	sprite->current_frame = 0;
	sprite->last_frame_time = 0.0;
	sprite->distance = 0.0;
	sprite->frame_count = 0;
	init_sprite_frames(sprite);
}

void	init_animated_sprite_in_asset(t_asset *asset)
{
	if (!asset)
		return ;
	init_animated_sprite_config(&asset->animated_sprite);
}

void	init_map(t_map *map)
{
	int	i;

	map->grid = NULL;
	map->door_states = NULL;
	map->door_openness = NULL;
	map->width = 0;
	map->height = 0;
	map->sprite_count = 0;
	i = 0;
	while (i < MAX_SPRITES)
	{
		init_single_sprite(&map->sprites[i]);
		i++;
	}
}
