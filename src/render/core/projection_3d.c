/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   projection_3d.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/23 13:39:14 by jianisong     #+#    #+#                 */
/*   Updated: 2025/06/11 21:35:22 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static t_point	calculate_wall_start(int line_height, int i)
{
	t_point	wall_start;

	wall_start.x = i;
	wall_start.y = -line_height / 2 + HEIGHT / 2;
	if (wall_start.y < 0)
		wall_start.y = 0;
	return (wall_start);
}

static t_point	calculate_wall_end(int line_height, int i)
{
	t_point	wall_end;

	wall_end.x = i;
	wall_end.y = line_height / 2 + HEIGHT / 2;
	if (wall_end.y >= HEIGHT)
		wall_end.y = HEIGHT - 1;
	return (wall_end);
}

static void	init_render_data(t_game *game, int i, t_render_data *data)
{
	data->per_dist = game->rays[i].dist * cos(game->rays[i].angle_offset);
	if (data->per_dist < MIN_PER_DIST)
		data->per_dist = MIN_PER_DIST;
	data->line_height = (int)HEIGHT / data->per_dist;
	data->draw_start = calculate_wall_start(data->line_height, i);
	data->draw_end = calculate_wall_end(data->line_height, i);
}

/**
 * Render 3d projection to the screen
 * 1. Calculate perpendicular ray distance to remove fish-eye distortion
 * 2. Calculate Wall height based on distance to simulate perspective:
 *    closer wall appears taller
 * 3. Draw ceiling above the wall and floor below the wall
 */
void	render_3d_projection(t_game *game)
{
	t_render_data	data;
	int				i;

	i = 0;
	while (i < WIDTH)
	{
		data.x = i;
		init_render_data(game, i, &data);
		draw_ceiling(game->img, data.draw_start, &game->asset.ceiling);
		create_wall_info(game, i, &data.wall_info);
		draw_textured_wall(game, &data);
		draw_floor(game->img, data.draw_end, &game->asset.floor);
		i++;
	}
}
