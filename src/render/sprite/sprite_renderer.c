/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_renderer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 11:11:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:41:11 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	render_single_sprite(t_game *game, t_sprite *sprite)
{
	t_sprite_render	render;
	int				stripe;

	if (sprite->distance <= 0)
		return ;
	calculate_sprite_screen_pos(game, sprite, &render);
	if (render.screen_x < -render.sprite_width / 2
		|| render.screen_x > WIDTH + render.sprite_width / 2)
		return ;
	stripe = render.draw_start_x;
	while (stripe < render.draw_end_x)
	{
		draw_sprite_column(game, sprite, &render, stripe);
		stripe++;
	}
}

void	render_sprites(t_game *game)
{
	int	i;

	calculate_sprite_distances(game);
	sort_sprites_by_distance(game);
	i = 0;
	while (i < game->map.sprite_count)
	{
		render_single_sprite(game, &game->map.sprites[i]);
		i++;
	}
}
