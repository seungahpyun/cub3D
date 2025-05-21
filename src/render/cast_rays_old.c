/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays_old.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 11:14:45 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/21 15:57:58 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	init_ray(t_player *player, double ray_angle, t_ray *ray)
{
	ray->start_x = (player->x + 0.5) * MINIMAP_CELL_SIZE;
	ray->start_y = (player->y + 0.5) * MINIMAP_CELL_SIZE;
	ray->end_x = ray->start_x;
	ray->end_y = ray->start_y;
	ray->angle = ray_angle;
}

void	find_first_inter_horizon(t_ray *ray, double player_angle)
{
	if (player_angle <= M_PI)
		ray->end_y = (int)(ray->start_y / MINIMAP_CELL_SIZE) * MINIMAP_CELL_SIZE
			- 1;
	else
		ray->end_y = (int)(ray->start_y / MINIMAP_CELL_SIZE) * MINIMAP_CELL_SIZE
			+ MINIMAP_CELL_SIZE;
	ray->end_x = ray->start_x + (ray->start_y - ray->end_y) / tan(ray->angle);
}

void	find_next_inter_horizon(t_ray *ray, double player_angle, double dy)
{
	double	x_inc;
	double	y_inc;

	if (player_angle <= M_PI)
		y_inc = dy;
	else
		y_inc = -dy;
	x_inc = y_inc / tan(ray->angle);
	ray->end_x += x_inc;
	ray->end_y -= y_inc;
	// printf("Before converting to int (%f, %f) \n", ray->end_x, ray->end_y);
}

void	find_hit_point_horizon(t_map *map, t_player *player, t_ray *ray)
{
	int	hit;

	hit = 0;
	find_first_inter_horizon(ray, player->angle);
	hit = check_hit_wall(map, ray);
	while (!hit)
	{
		find_next_inter_horizon(ray, player->angle, MINIMAP_CELL_SIZE);
		hit = check_hit_wall(map, ray);
	}
}

void	find_first_inter_vertical(t_ray *ray, double player_angle)
{
	if (player_angle <= M_PI / 2 || player_angle >= 3 * M_PI / 2)
		ray->end_x = (int)(ray->start_x / MINIMAP_CELL_SIZE) * MINIMAP_CELL_SIZE
			+ MINIMAP_CELL_SIZE;
	else
		ray->end_x = (int)(ray->start_x / MINIMAP_CELL_SIZE) * MINIMAP_CELL_SIZE
			- 1;
	ray->end_y = ray->start_y - (ray->end_x - ray->start_x) / tan(ray->angle);
}

void	find_next_inter_vertical(t_ray *ray, double player_angle, double dx)
{
	double	x_inc;
	double	y_inc;

	if (player_angle <= M_PI / 2 || player_angle >= 3 * M_PI / 2)
		x_inc = dx;
	else
		x_inc = -dx;
	y_inc = x_inc * tan(ray->angle);
	ray->end_x += x_inc;
	ray->end_y -= y_inc;
	// printf("Before converting to int (%d, %d) \n", ray->end_x, ray->end_y);
}

void	find_hit_point_vertical(t_map *map, t_player *player, t_ray *ray)
{
	int	hit;

	hit = 0;
	find_first_inter_vertical(ray, player->angle);
	hit = check_hit_wall(map, ray);
	while (!hit)
	{
		find_next_inter_vertical(ray, player->angle, MINIMAP_CELL_SIZE);
		hit = check_hit_wall(map, ray);
	}
}

void	test_rays(t_game *game)
{
	t_ray	ray;
	double	ray_angle;

	// t_point	inter;
	ray_angle = game->player.angle + degree_to_radian(0.5 * FOV);
	printf("ray_angle is %f\n", ray_angle);
	init_ray(&game->player, ray_angle, &ray);
	// find_hit_point_horizon(&game->map, &game->player, &ray);
	find_hit_point_vertical(&game->map, &game->player, &ray);
	// printf("Find interection (%d,%d) from player(%d,% d) and ray_angle %f\n",
	// 	(int)round(ray.end_x) - 1, (int)round(ray.end_y) - 1, game->player.x,
	// 	game->player.y, ray_angle);
}
