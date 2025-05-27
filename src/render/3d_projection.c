/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3d_projection.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/23 13:39:14 by jianisong     #+#    #+#                 */
/*   Updated: 2025/05/27 14:37:17 by spyun         ########   odam.nl         */
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

static void	draw_ceiling(mlx_image_t *img, t_point wall_start, t_color *color)
{
	t_point	ceiling_start;
	int		ceiling_color;

	ceiling_start.x = wall_start.x;
	ceiling_start.y = 0;
	ceiling_color = color_to_rgba(color, 255);
	draw_line(img, ceiling_start, wall_start, ceiling_color);
}

static void	draw_floor(mlx_image_t *img, t_point wall_end, t_color *color)
{
	int		floor_color;
	t_point	floor_end;

	floor_end.x = wall_end.x;
	floor_end.y = HEIGHT - 1;
	floor_color = color_to_rgba(color, 255);
	draw_line(img, wall_end, floor_end, floor_color);
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
	double	per_dist;
	int		i;
	int		line_height;
	t_point	wall_start;
	t_point	wall_end;

	i = 0;
	while (i < WIDTH)
	{
		per_dist = game->rays[i].dist * cos(game->rays[i].angle_offset);
		if (per_dist < MIN_PER_DIST)
			per_dist = MIN_PER_DIST;
		line_height = (int)HEIGHT / per_dist;
		wall_start = calculate_wall_start(line_height, i);
		wall_end = calculate_wall_end(line_height, i);
		draw_ceiling(game->img, wall_start, &game->asset.ceiling);
		draw_line(game->img, wall_start, wall_end, 0x000000FF);
		draw_floor(game->img, wall_end, &game->asset.floor);
		i++;
	}
}
