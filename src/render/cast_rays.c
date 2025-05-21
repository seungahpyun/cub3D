/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cast_rays.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 14:19:16 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/21 17:39:18 by jsong         ########   odam.nl         */
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
	ray->ray_inc_x = fabs(1 / cos(ray->angle));
	ray->ray_inc_y = fabs(1 / sin(ray->angle));
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
 * Cast a ray from player position until it hit a wall
 * 1. Determine which boundary the ray will hit first
 *  -compare hit_dist_x and hit_dist_y value
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
		if (ray->hit_dist_x < ray->hit_dist_y)
		{
			ray->hit_dist_x += ray->ray_inc_x;
			ray->map_x += ray->step_x;
			ray->hit_side = 'x';
		}
		else
		{
			ray->hit_dist_y += ray->ray_inc_y;
			ray->map_y += ray->step_y;
			ray->hit_side = 'y';
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
	ray_angle = game->player.angle + degree_to_radian(0.5 * FOV);
	printf("ray_angle is %f\n", ray_angle);
	init_ray(&game->player, ray_angle, &ray);
	cast_ray(game, &ray);
}
