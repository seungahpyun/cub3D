/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 15:03:34 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/12 10:11:01 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static double	calculate_door_x(t_wall_info *wall_info, t_door *door)
{
	double	door_x;

	if (door->type == DOOR_VERTICAL)
		door_x = wall_info->hit_y;
	else
		door_x = wall_info->hit_x;
	door_x = door_x - floor(door_x);
	return (door_x);
}

static void	init_door_texture_data(t_game *game, t_render_data *render_data,
		t_door *door, t_texture_data *data)
{
	double	visible_portion;

	if (!game || !render_data || !door || !data)
		return ;
	if (!game->asset.door_img)
		return ;
	data->texture = game->asset.door_img;
	data->wall_x = calculate_door_x(&render_data->wall_info, door);
	visible_portion = 1 - door->openness;
	data->tex_x = (int)(data->wall_x * data->texture->width * visible_portion);
	if (data->tex_x >= (int)data->texture->width)
		data->tex_x = data->texture->width - 1;
	calculate_wall_params(render_data->line_height, &data->params);
}

void	draw_textured_door(t_game *game, t_render_data *render_data)
{
	t_texture_data	data;
	int				i;
	int				cx;
	int				cy;
	t_door			*door;

	if (!game || !render_data)
		return ;
	i = render_data->x;
	cx = game->rays[i].map_x;
	cy = game->rays[i].map_y;
	door = &game->map.doors[cy][cx];
	init_door_texture_data(game, render_data, door, &data);
	if (!data.texture)
		return ;
	draw_wall_pixels(game, render_data->x, render_data->draw_start, &data);
}
