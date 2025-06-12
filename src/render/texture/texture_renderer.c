/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_renderer.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/29 11:50:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/12 10:03:03 by jianisong     ########   odam.nl         */
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

void	calculate_wall_params(int line_height, t_wall_params *params)
{
	int	wall_center;

	if (!params)
		return ;
	params->full_wall_height = line_height;
	wall_center = HEIGHT / 2;
	params->wall_top = wall_center - params->full_wall_height / 2;
	params->wall_bottom = wall_center + params->full_wall_height / 2;
}

static void	init_texture_data(t_game *game, t_wall_info *wall_info,
		int line_height, t_texture_data *data)
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
	calculate_wall_params(line_height, &data->params);
}

void	draw_textured_wall(t_game *game, t_render_data *render_data)
{
	t_texture_data	data;

	if (!game || !render_data)
		return ;
	init_texture_data(game, &render_data->wall_info, render_data->line_height,
		&data);
	if (!data.texture)
		return ;
	draw_wall_pixels(game, render_data->x, render_data->draw_start, &data);
}
