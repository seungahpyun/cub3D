/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_renderer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/29 11:50:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/02 11:09:51 by spyun         ########   odam.nl         */
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

static void	calculate_wall_params(t_game *game, t_wall_info *wall_info,
				int *full_wall_height, int *wall_top, int *wall_bottom)
{
	double	per_dist;
	int		wall_center;

	per_dist = sqrt(pow(wall_info->hit_x - game->player.x, 2)
			+ pow(wall_info->hit_y - game->player.y, 2));
	per_dist *= cos(wall_info->ray_angle - game->player.angle);
	if (per_dist < MIN_PER_DIST)
		per_dist = MIN_PER_DIST;
	*full_wall_height = (int)(HEIGHT / per_dist);
	wall_center = HEIGHT / 2;
	*wall_top = wall_center - *full_wall_height / 2;
	*wall_bottom = wall_center + *full_wall_height / 2;
}

void	draw_textured_wall(t_game *game, int x, t_point wall_start,
			t_point wall_end, t_wall_info *wall_info)
{
	mlx_image_t	*texture;
	double		wall_x;
	int			tex_x;
	int			full_wall_height;
	int			wall_top;
	int			wall_bottom;
	double		tex_step;
	double		tex_pos;
	int			y;

	texture = get_wall_texture(game, wall_info);
	if (!texture)
		return ;
	wall_x = calculate_wall_x(wall_info);
	tex_x = (int)(wall_x * texture->width);
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	calculate_wall_params(game, wall_info, &full_wall_height,
		&wall_top, &wall_bottom);
	tex_step = (double)texture->height / (double)full_wall_height;
	tex_pos = (wall_start.y - wall_top) * tex_step;
	y = wall_start.y;
	while (y <= wall_end.y)
	{
		int tex_y = (int)tex_pos;
		if (tex_y >= 0 && tex_y < (int)texture->height)
		{
			int color = get_texture_pixel(texture, tex_x, tex_y);
			if (is_within_boundary(x, y, game->img->width, game->img->height))
				mlx_put_pixel(game->img, x, y, color);
		}
		tex_pos += tex_step;
		y++;
	}
}
