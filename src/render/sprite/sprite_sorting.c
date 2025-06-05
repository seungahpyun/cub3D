/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_sorting.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:37:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:40:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
			if (game->map.sprites[j].distance
				< game->map.sprites[j + 1].distance)
			{
				swap_sprites(&game->map.sprites[j], &game->map.sprites[j + 1]);
			}
			j++;
		}
		i++;
	}
}
