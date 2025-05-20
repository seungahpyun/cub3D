/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 11:14:45 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/20 15:46:53 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_point	find_next_inter_horizon(t_ray *ray, double player_angle, double dy)
{
	double	x_inc;
	double	y_inc;
	t_point	next;

	if (player_angle <= M_PI)
		y_inc = dy;
	else
		y_inc = -dy;
	x_inc = y_inc / tan(ray->angle);
	ray->end_x += x_inc;
	ray->end_y -= y_inc;
	printf("Before converting to int (%f, %f) \n", ray->end_x, ray->end_y);
	next.x = (int)ray->end_x;
	next.y = (int)ray->end_y;
	printf("Find interection (%d,%d) and ray_angle %f\n", next.x, next.y,
		ray->angle);
	return (next);
}

t_point	find_first_interection_horizon(t_ray *ray, double player_angle)
{
	t_point	point;

	point = find_next_inter_horizon(ray, player_angle, 0.5);
	return (point);
}

void	init_ray(t_player *player, double ray_angle, t_ray *ray)
{
	ray->start_x = player->x;
	ray->start_y = player->y;
	ray->end_x = player->x;
	ray->end_y = player->y;
	ray->angle = ray_angle;
}

t_point	find_hit_point_horizon(t_map *map, t_player *player, t_ray *ray)
{
	int		hit;
	t_point	point;
	int		mx;
	int		my;

	hit = 0;
	point = find_first_interection_horizon(ray, player->angle);
	mx = point.x;
	my = point.y;
	if (is_valid_point(map, mx, my) && map->grid[my][mx] == '1')
		hit = 1;
	while (!hit)
	{
		point = find_next_inter_horizon(ray, player->angle, 1.0);
		mx = point.x;
		my = point.y;
		if (is_valid_point(map, mx, my) && map->grid[my][mx] == '1')
			hit = 1;
	}
	return (point);
}

void	test_rays(t_game *game)
{
	t_ray	ray;
	double	ray_angle;
	t_point	inter;

	ray_angle = game->player.angle + degree_to_radian(0.5 * FOV);
	init_ray(&game->player, ray_angle, &ray);
	inter = find_hit_point_horizon(&game->map, &game->player, &ray);
	printf("Find interection (%d,%d) from player(%d,% d) and ray_angle %f\n",
		inter.x, inter.y, game->player.x, game->player.y, ray_angle);
}
