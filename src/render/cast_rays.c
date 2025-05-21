/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 14:19:16 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/21 16:32:57 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	calculate_initial_distance(t_ray *ray)
{
	if (ray->angle <= M_PI / 2 || ray->angle >= 3 * M_PI / 2)
	{
		ray->step_x = 1;
		ray->hit_dist_x = (ray->map_x + 1.0 - ray->start_x) * ray->ray_inc_x;
	}
	else
	{
		ray->step_x = -1;
		ray->hit_dist_x = (ray->start_x - ray->map_x) * ray->ray_inc_x;
	}
	if (ray->angle <= M_PI)
	{
		ray->step_y = -1;
		ray->hit_dist_y = (ray->start_y - ray->map_y) * ray->ray_inc_y;
	}
	else
	{
		ray->step_y = 1;
		ray->hit_dist_y = (ray->map_y + 1.0 - ray->start_y) * ray->ray_inc_y;
	}
}

/**
 * Initialize a ray
 */
void	init_ray(t_player *player, double ray_angle, t_ray *ray)
{
	ray->start_x = player->x;
	ray->start_y = player->y;
	ray->map_x = (int)ray->start_x;
	ray->map_y = (int)ray->start_y;
	ray->angle = ray_angle;
	ray->ray_inc_x = abs(1 / cos(ray->angle));
	ray->ray_inc_y = abs(1 / sin(ray->angle));
	calculate_initial_distance(ray);
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
 * Cast a ray from player position and get distance
 * 1. Calculate step directions and initial
 *
 * 2. Move to Nearest line
 *  - compare which grid line the ray will hit first
 *  - move the ray to that intersection point
 * 3. Check if you've hit a wall at the new grid cell
 *  - if no hit, repeat the previous process
 * 4. Calculate the final distance and return
 */
double	cast_ray(t_game *game, t_ray *ray)
{
	bool hit;
	hit = false;
	while (!hit)
	{
		if (ray->hit_dist_x < ray->hit_dist_y)
		{
			ray->hit_dist_x += ray->ray_inc_x;
			ray->map_x += ray->step_x;
			ray->hit_side = 'x';
		}

		hit = check_hit_wall(&game->map, ray);
	}
}