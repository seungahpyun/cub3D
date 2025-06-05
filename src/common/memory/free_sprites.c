/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:55:40 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:58:57 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	free_sprite_frames(mlx_t *mlx, t_sprite *sprite)
{
	int	frame;
	int	max_frames;

	if (sprite->type == SPRITE_TREE)
		max_frames = TREE_FRAMES;
	else
		return ;
	frame = 0;
	while (frame < max_frames)
	{
		if (sprite->frames[frame])
		{
			mlx_delete_image(mlx, sprite->frames[frame]);
			sprite->frames[frame] = NULL;
		}
		frame++;
	}
}

void	free_all_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.sprite_count)
	{
		free_sprite_frames(game->mlx, &game->map.sprites[i]);
		i++;
	}
}
