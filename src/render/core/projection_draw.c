/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   projection_draw.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/02 11:38:16 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/11 21:59:45 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_ceiling(mlx_image_t *img, t_point wall_start, t_color *color)
{
	t_point	ceiling_start;
	int		ceiling_color;

	ceiling_start.x = wall_start.x;
	ceiling_start.y = 0;
	ceiling_color = color_to_rgba(color, 255);
	draw_line(img, ceiling_start, wall_start, ceiling_color);
}

void	draw_floor(mlx_image_t *img, t_point wall_end, t_color *color)
{
	int		floor_color;
	t_point	floor_end;

	floor_end.x = wall_end.x;
	floor_end.y = HEIGHT - 1;
	floor_color = color_to_rgba(color, 255);
	draw_line(img, wall_end, floor_end, floor_color);
}

void	create_wall_info(t_game *game, int i, t_wall_info *wall_info)
{
	double	ray_angle;
	double	ray_dist;

	ray_angle = game->rays[i].angle;
	ray_dist = game->rays[i].dist;
	wall_info->ray_angle = ray_angle;
	wall_info->hit_x = game->player.x + cos(ray_angle) * ray_dist;
	wall_info->hit_y = game->player.y - sin(ray_angle) * ray_dist;
	wall_info->hit_side = game->rays[i].hit_side;
}
