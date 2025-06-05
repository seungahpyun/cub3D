/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_pixel.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 11:44:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 14:25:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
			color = get_pixel_color(data->texture, data->tex_x, tex_y);
			if (is_within_boundary(x, y, game->img->width, game->img->height))
				mlx_put_pixel(game->img, x, y, color);
		}
		tex_pos += tex_step;
		y++;
	}
}
