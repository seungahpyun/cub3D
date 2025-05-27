/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_ray.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/23 17:00:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/27 16:19:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_single_ray(t_game *game, t_point start, int i)
{
	t_point	end;
	double	adjusted_distance;

	adjusted_distance = game->rays[i].dist;
	end.x = start.x + cos(game->rays[i].angle)
		* adjusted_distance * MINIMAP_CELL_SIZE;
	end.y = start.y - sin(game->rays[i].angle)
		* adjusted_distance * MINIMAP_CELL_SIZE;
	if (end.x >= 0 && end.x < MINIMAP_W && end.y >= 0 && end.y < MINIMAP_H
		&& start.x >= 0 && start.x < MINIMAP_W
		&& start.y >= 0 && start.y < MINIMAP_H)
		draw_line(game->minimap.img, start, end, MINIMAP_RAY_COLOR);
}

/**
 * Draws rays on minimap from the player:
 * 1. Calculate the ray angle and distiance to get hit point of ray
 * 2. Map map_corrdinates to minimap image position
 * 3. Draw the line on the minimap buffer
 */
void	draw_minimap_rays(t_game *game)
{
	t_point	start;
	int		i;

	calculate_player_screen_pos(game, &start);
	i = 0;
	while (i < WIDTH)
	{
		draw_single_ray(game, start, i);
		i++;
	}
}
