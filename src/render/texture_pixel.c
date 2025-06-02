/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_pixel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 11:44:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/02 11:49:24 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	get_texture_pixel(mlx_image_t *texture, int tex_x, int tex_y)
{
	int			pixel_index;
	uint8_t		*pixel_ptr;
	uint32_t	color;

	if (!texture || !texture->pixels)
		return (0x001f1f1f);
	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0x001f1f1f);
	pixel_index = (tex_y * texture->width + tex_x) * 4;
	pixel_ptr = texture->pixels + pixel_index;
	color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
		| (pixel_ptr[2] << 8) | pixel_ptr[3];
	return (color);
}

void	draw_wall_pixels(t_game *game, int x, t_point wall_start,
				t_texture_data *data)
{
	double	tex_step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	tex_step = (double)data->texture->height
		/ (double)data->params.full_wall_height;
	tex_pos = (wall_start.y - data->params.wall_top) * tex_step;
	y = wall_start.y;
	while (y <= data->params.wall_bottom && y < HEIGHT)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= 0 && tex_y < (int)data->texture->height)
		{
			color = get_texture_pixel(data->texture, data->tex_x, tex_y);
			if (is_within_boundary(x, y, game->img->width, game->img->height))
				mlx_put_pixel(game->img, x, y, color);
		}
		tex_pos += tex_step;
		y++;
	}
}
