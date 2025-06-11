/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_cast_ray.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/11 12:54:43 by jianisong     #+#    #+#                 */
/*   Updated: 2025/06/11 21:16:31 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	hit_vertical_door(t_door *door, t_ray *ray, double *door_dist)
{
	double	dist;
	double	hit_x;
	double	hit_y;
	bool	hit;

	if (fabs(ray->dir_x) < 1e-9)
		return (false);
	hit_x = door->mx + 0.5;
	dist = (hit_x - ray->start_x) / ray->dir_x;
	hit_y = ray->start_y - ray->dir_y * dist;
	hit = (hit_y >= door->my && hit_y <= (door->my + 1.0 - door->openness));
	if (hit)
	{
		*door_dist = dist;
		ray->hit_door = true;
		return (true);
	}
	return (false);
}

static bool	hit_horizontal_door(t_door *door, t_ray *ray, double *door_dist)
{
	double	dist;
	double	hit_x;
	double	hit_y;
	bool	hit;

	if (fabs(ray->dir_y) < 1e-9)
		return (false);
	hit_y = door->my + 0.5;
	dist = (ray->start_y - hit_y) / ray->dir_y;
	hit_x = ray->start_x + ray->dir_x * dist;
	hit = (hit_x >= door->mx && hit_x <= (door->mx + 1.0 - door->openness));
	if (hit)
	{
		*door_dist = dist;
		ray->hit_door = true;
		return (true);
	}
	return (false);
}

bool	hit_door(t_door *door, t_ray *ray, double *door_dist)
{
	if (door->type == DOOR_VERTICAL)
		return (hit_vertical_door(door, ray, door_dist));
	else
		return (hit_horizontal_door(door, ray, door_dist));
}
