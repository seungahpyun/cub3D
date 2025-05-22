/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 14:19:16 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/22 10:37:49 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	calculate_dist_inc(t_ray *ray)
{
	if (fabs(ray->dir_x) < 1e-9)
		ray->dist_inc_x = INFINITY;
	else
		ray->dist_inc_x = fabs(1.0 / ray->dir_x);
	if (fabs(ray->dir_y) < 1e-9)
		ray->dist_inc_y = INFINITY;
	else
		ray->dist_inc_y = fabs(1.0 / ray->dir_y);
}

static void	calculate_initial_dist(t_ray *ray)
{
	if (ray->dir_x > 0)
	{
		ray->step_x = 1;
		ray->dist_to_v = (ray->map_x + 1.0 - ray->start_x) * ray->dist_inc_x;
	}
	else
	{
		ray->step_x = -1;
		ray->dist_to_v = (ray->start_x - ray->map_x) * ray->dist_inc_x;
	}
	if (ray->dir_y > 0)
	{
		ray->step_y = -1;
		ray->dist_to_h = (ray->start_y - ray->map_y) * ray->dist_inc_y;
	}
	else
	{
		ray->step_y = 1;
		ray->dist_to_h = (ray->map_y + 1.0 - ray->start_y) * ray->dist_inc_y;
	}
}

/**
 * Initialize a ray with player position and ray_angle
 * 1.initialize start position and current square position
 * 2.calculate the distance the ray has to travel for 1 unit x or 1 unit y
 * 3.calculate initial distance the ray has to travel to first x_side and y_side
 */
void	init_ray(t_player *player, double ray_angle, t_ray *ray)
{
	ray->start_x = player->x;
	ray->start_y = player->y;
	ray->map_x = (int)ray->start_x;
	ray->map_y = (int)ray->start_y;
	ray->angle = ray_angle;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	calculate_dist_inc(ray);
	calculate_initial_dist(ray);
}

bool	check_hit_wall(t_map *map, t_ray *ray)
{
	printf("Checked point is (%d, %d) \n", ray->map_x, ray->map_y);
	if (is_valid_point(map, ray->map_x, ray->map_y)
		&& map->grid[ray->map_y][ray->map_x] == '0')
		return (false);
	return (true);
}

/**
 * Cast a ray from player position until it hit a wall
 * 1. Determine which boundary the ray will hit first
 *  -compare dist_to_v and dist_to_horiz value
 *  - move the ray to that intersection point
 * 2. Update the distance to the next boundary of that type
 * 3. Check if you've hit a wall at this new grid cell
 *  - if no hit, repeat the previous process
 * 4. Calculate the final distance and return
 */
double	cast_ray(t_game *game, t_ray *ray)
{
	bool	hit;
	double	distance;

	hit = false;
	while (!hit)
	{
		if (ray->dist_to_v < ray->dist_to_h)
		{
			ray->dist_to_v += ray->dist_inc_x;
			ray->map_x += ray->step_x;
			ray->hit_side = 'v';
		}
		else
		{
			ray->dist_to_h += ray->dist_inc_y;
			ray->map_y += ray->step_y;
			ray->hit_side = 'h';
		}
		hit = check_hit_wall(&game->map, ray);
	}
	// distance = calculate_distance_to_wall(ray);
	distance = 10;
	return (distance);
}

void	test_rays(t_game *game)
{
	t_ray	ray;
	double	ray_angle;

	// t_point	inter;
	printf("player_angle is %f\n", game->player.angle);
	ray_angle = game->player.angle;
	init_ray(&game->player, ray_angle, &ray);
	printf("ray_angle is %f, dist_inc_x is %f, dist_inc_y is %f\n", ray_angle,
		ray.dist_inc_x, ray.dist_inc_y);
	cast_ray(game, &ray);
}
