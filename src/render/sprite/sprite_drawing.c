/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_drawing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:37:48 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/10 14:42:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	get_texture_x_coord(t_sprite *sprite, t_sprite_render *render,
							int stripe)
{
	mlx_image_t	*texture;
	int			tex_x;

	texture = sprite->frames[sprite->current_frame];
	if (!texture)
		return (-1);
	tex_x = (int)(256 * (stripe - (-render->sprite_width / 2
					+ (int)render->screen_x)) * texture->width
			/ render->sprite_width) / 256;
	if (tex_x < 0 || tex_x >= (int)texture->width)
		return (-1);
	return (tex_x);
}

static void	draw_sprite_pixels(t_game *game, t_sprite_draw_data *data)
{
	int			y;
	int			tex_y;
	uint32_t	color;
	mlx_image_t	*texture;

	texture = data->sprite->frames[data->sprite->current_frame];
	y = data->render->draw_start_y;
	while (y < data->render->draw_end_y)
	{
		tex_y = (((y * 256 - HEIGHT * 128 + data->render->sprite_height * 128)
					* texture->height) / data->render->sprite_height) / 256;
		color = get_pixel_color(texture, data->tex_x, tex_y);
		if ((color & 0xFF) > 0
			&& game->rays[data->stripe].dist > data->sprite->distance)
		{
			if (is_within_boundary(data->stripe, y,
					game->img->height, game->img->width))
				mlx_put_pixel(game->img, data->stripe, y, color);
		}
		y++;
	}
}

void	draw_sprite_column(t_game *game, t_sprite *sprite,
							t_sprite_render *render, int stripe)
{
	t_sprite_draw_data	data;

	data.sprite = sprite;
	data.render = render;
	data.stripe = stripe;
	data.tex_x = get_texture_x_coord(sprite, render, stripe);
	if (data.tex_x == -1)
		return ;
	draw_sprite_pixels(game, &data);
}
