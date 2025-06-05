/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_drawing.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:37:48 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:53:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static uint32_t	get_sprite_pixel(mlx_image_t *texture, int tex_x, int tex_y)
{
	int			pixel_index;
	uint8_t		*pixel_ptr;
	uint32_t	color;

	if (!texture || !texture->pixels)
		return (0);
	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0);
	pixel_index = (tex_y * texture->width + tex_x) * 4;
	pixel_ptr = texture->pixels + pixel_index;
	color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
		| (pixel_ptr[2] << 8) | pixel_ptr[3];
	return (color);
}

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
		color = get_sprite_pixel(texture, data->tex_x, tex_y);
		if ((color & 0xFF) > 0
			&& game->rays[data->stripe].dist > data->sprite->distance)
		{
			if (is_within_boundary(data->stripe, y, game->img->width,
					game->img->height))
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
