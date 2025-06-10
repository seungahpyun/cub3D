/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_player.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:31:48 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 18:49:12 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/**
 * Draws rays on minimap from the player:
 * 1. Calculate the ray angle and distiance to get hit point of ray
 * 2. Map map_corrdinates to minimap image position
 * 3. Draw the line on the minimap buffer
 */
void	draw_minimap_rays(t_ray_data *rays, t_minimap *minimap)
{
	double	ray_angle;
	double	dist;
	t_point	start;
	t_point	end;
	int		i;

	start.x = MINIMAP_W / 2;
	start.y = MINIMAP_H / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray_angle = rays[i].angle;
		dist = rays[i].dist;
		end.x = start.x + cos(ray_angle) * dist * MINIMAP_CELL_SIZE;
		end.y = start.y - sin(ray_angle) * dist * MINIMAP_CELL_SIZE;
		draw_line(minimap->img, start, end, MINIMAP_RAY_COLOR);
		i++;
	}
}

void	draw_minimap_player(t_player *player, t_minimap *minimap)
{
	t_cell	player_cell;
	t_point	player_start;
	t_point	player_end;

	player_cell.size = MINIMAP_CELL_SIZE / 3;
	player_cell.px = MINIMAP_W / 2 - player_cell.size / 2;
	player_cell.py = MINIMAP_H / 2 - player_cell.size / 2;
	player_cell.color = MINIMAP_PLAYER_COLOR;
	draw_cell(minimap->img, player_cell);
	player_start.x = MINIMAP_W / 2;
	player_start.y = MINIMAP_H / 2;
	player_end.x = player_start.x + cos(player->angle) * MINIMAP_CELL_SIZE;
	player_end.y = player_start.y - sin(player->angle) * MINIMAP_CELL_SIZE;
	draw_line(minimap->img, player_start, player_end, RED);
}
