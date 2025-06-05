/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_animation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:37:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:43:25 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	get_max_frames(t_sprite_type type)
{
	if (type == SPRITE_TREE)
		return (TREE_FRAMES);
	return (1);
}

static void	update_single_sprite_animation(t_sprite *sprite,
										double current_time)
{
	int		max_frames;
	double	time_diff;

	max_frames = get_max_frames(sprite->type);
	time_diff = current_time - sprite->last_frame_time;
	if (time_diff >= SPRITE_ANIMATION_SPEED)
	{
		sprite->current_frame++;
		if (sprite->current_frame >= max_frames)
			sprite->current_frame = 0;
		sprite->last_frame_time = current_time;
	}
}

void	update_sprite_animations(t_game *game)
{
	int		i;
	double	current_time;

	current_time = mlx_get_time();
	i = 0;
	while (i < game->map.sprite_count)
	{
		update_single_sprite_animation(&game->map.sprites[i], current_time);
		i++;
	}
}
