/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_renderer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/29 11:50:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/02 13:47:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static mlx_image_t	*get_wall_texture(t_game *game, t_wall_info *wall_info)
{
	if (!game || !wall_info || !game->asset.no_img || !game->asset.so_img
		|| !game->asset.we_img || !game->asset.ea_img)
		return (NULL);
	if (wall_info->hit_side == HIT_SIDE_VERTICAL)
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

	if (wall_info->hit_side == HIT_SIDE_VERTICAL)
		wall_x = wall_info->hit_y;
	else
		wall_x = wall_info->hit_x;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}

static void	calculate_wall_params(t_game *game, t_wall_info *wall_info,
				t_wall_params *params)
{
	double	per_dist;
	int		wall_center;

	if (!game || !wall_info || !params)
		return ;
	per_dist = sqrt(pow(wall_info->hit_x - game->player.x, 2)
				+ pow(wall_info->hit_y - game->player.y, 2));
	per_dist *= cos(wall_info->ray_angle - game->player.angle);
	if (per_dist < MIN_PER_DIST)
		per_dist = MIN_PER_DIST;
	params->full_wall_height = (int)(HEIGHT / per_dist);
	wall_center = HEIGHT / 2;
	params->wall_top = wall_center - params->full_wall_height / 2;
	params->wall_bottom = wall_center + params->full_wall_height / 2;
}

static void	init_texture_data(t_game *game, t_wall_info *wall_info,
				t_texture_data *data)
{
	if (!game || !wall_info || !data)
		return ;
	data->texture = get_wall_texture(game, wall_info);
	if (!data->texture)
		return ;
	data->wall_x = calculate_wall_x(wall_info);
	data->tex_x = (int)(data->wall_x * data->texture->width);
	if (data->tex_x >= (int)data->texture->width)
		data->tex_x = data->texture->width - 1;
	calculate_wall_params(game, wall_info, &data->params);
}

void	draw_textured_wall(t_game *game, int x, t_point wall_start,
			t_wall_info *wall_info)
{
	t_texture_data	data;

	if (!game || !wall_info)
		return ;
	init_texture_data(game, wall_info, &data);
	if (!data.texture)
		return ;
	draw_wall_pixels(game, x, wall_start, &data);
}
