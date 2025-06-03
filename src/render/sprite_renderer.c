/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_renderer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 11:11:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/03 16:02:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	get_max_frames(t_sprite_type type)
{
	if (type == SPRITE_TREE)
		return (TREE_FRAMES);
	return (1);
}

static void	update_single_sprite_animation(t_sprite *sprite, double current_time)
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

void	calculate_sprite_distances(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < game->map.sprite_count)
	{
		dx = game->map.sprites[i].x - game->player.x;
		dy = game->map.sprites[i].y - game->player.y;
		game->map.sprites[i].distance = sqrt(dx * dx + dy * dy);
		i++;
	}
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_sprites_by_distance(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.sprite_count - 1)
	{
		j = 0;
		while (j < game->map.sprite_count - i - 1)
		{
			if (game->map.sprites[j].distance < game->map.sprites[j + 1].distance)
			{
				swap_sprites(&game->map.sprites[j], &game->map.sprites[j + 1]);
			}
			j++;
		}
		i++;
	}
}
