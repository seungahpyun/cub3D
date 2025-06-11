/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 14:19:16 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/11 17:27:15 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/**
 * Calculate the distance the ray must travel to cross one grid cell
 * along x or y.
 * If the ray direction component is nearly zero, the increment is infinite
 */
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

/**
 * Compute initial distances from the ray start position to the
 * first vertical and horizontal grid boundaries.
 * Also set the step direction for moving between grid cells.
 */
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
 * Initialize a ray for DDA-based grid traversal
 * - Set starting position and current map cell
 * - Compute direction vector from angle
 * - Precompute stepping increments and initial distances
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

static void	dda_step(t_ray *ray)
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
}

/**
 * Cast a ray from player position until it hit a wall
 * 1. Determine which boundary the ray will hit first
 *  - compare dist_to_v and dist_to_h value
 *  - extend the ray to that intersection point
 * 2. Update the distance to the next boundary of that type
 * 3. Check if you've hit a wall/door at this new grid cell
 *  - if no hit, repeat the previous process
 *  - if hit, calculate the final distance and return
 */
double	cast_ray(t_map *map, t_ray *ray)
{
	double	distance;
	char	c;
	double	door_dist;

	while (true)
	{
		dda_step(ray);
		c = map->grid[ray->map_y][ray->map_x];
		if (c == '1')
		{
			if (ray->hit_side == 'v')
				distance = ray->dist_to_v - ray->dist_inc_x;
			else
				distance = ray->dist_to_h - ray->dist_inc_y;
			return (distance);
		}
		if (c == 'D')
		{
			if (hit_door(&map->doors[ray->map_y][ray->map_x], ray, &door_dist))
				return (door_dist);
		}
	}
}
