/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_animation.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:37:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 19:34:59 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	update_single_sprite_animation(t_sprite *sprite,
										double current_time)
{
	double	time_diff;

	if (sprite->frame_count <= 1)
		return ;
	time_diff = current_time - sprite->last_frame_time;
	if (time_diff >= SPRITE_ANIMATION_SPEED)
	{
		sprite->current_frame++;
		if (sprite->current_frame >= sprite->frame_count)
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