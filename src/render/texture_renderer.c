/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_renderer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/29 11:50:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/02 09:57:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static mlx_image_t	*get_wall_texture(t_game *game, t_wall_info *wall_info)
{
	if (wall_info->hit_side == 'v')
	{
		if (wall_info->hit_x > game->player.x)
			return (game->asset.ea_img);
		else
			return (game->asset.we_img);
	}
	else
	{
		if (wall_info->hit_y > game->player.y)
			return (game->asset.so_img);
		else
			return (game->asset.no_img);
	}
}

static double	calculate_wall_x(t_wall_info *wall_info)
{
	double	wall_x;

	if (wall_info->hit_side == 'v')
		wall_x = wall_info->hit_y;
	else
		wall_x = wall_info->hit_x;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}

static int	get_texture_pixel(mlx_image_t *texture, int tex_x, int tex_y)
{
	int		pixel_index;
	uint8_t	*pixel_ptr;
	uint32_t	color;

	if (!texture || !texture->pixels)
		return (0x001f1f1f);
	if (tex_x < 0 || tex_x >= (int)texture->width ||
		tex_y < 0 || tex_y >= (int)texture->height)
		return (0x001f1f1f);
	pixel_index = (tex_y * texture->width + tex_x) * 4;
	pixel_ptr = texture->pixels + pixel_index;
	color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16) |
			(pixel_ptr[2] << 8) | pixel_ptr[3];
	return (color);
}

void	draw_textured_wall(t_game *game, int x, t_point wall_start,
			t_point wall_end, t_wall_info *wall_info)
{
	mlx_image_t	*texture;
	double		wall_x;
	int			tex_x;
	int			wall_height;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			y;
	int			color;

	texture = get_wall_texture(game, wall_info);
	if (!texture)
		return ;
	wall_x = calculate_wall_x(wall_info);
	tex_x = (int)(wall_x * (double)texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	wall_height = wall_end.y - wall_start.y;
	if (wall_height <= 0)
		return ;
	step = (double)texture->height / (double)wall_height;
	tex_pos = (wall_start.y - HEIGHT / 2 + wall_height / 2) * step;
	y = wall_start.y;
	while (y <= wall_end.y)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		color = get_texture_pixel(texture, tex_x, tex_y);
		if (is_within_boundary(x, y, game->img->width, game->img->height))
			mlx_put_pixel(game->img, x, y, color);
		y++;
	}
}
