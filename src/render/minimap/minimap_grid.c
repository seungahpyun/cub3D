/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_grid.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:31:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:34:56 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/**
 * Draws minimap grid showing walls and floor around player:
 * 1. Iterates through all map cells
 * 2. For each valid cell, calculates screen position using offset
 * 3. Draws cell with appropriate color based on map content
 */
void	draw_minimap_grid(t_map *map, t_minimap *minimap)
{
	int					mx;
	int					my;
	t_cell				cell;

	mx = 0;
	while (mx < map->width)
	{
		my = 0;
		while (my < map->height)
		{
			if (is_valid_point(map, mx, my))
			{
				cell.px = mx * MINIMAP_CELL_SIZE - minimap->offset_x;
				cell.py = my * MINIMAP_CELL_SIZE - minimap->offset_y;
				cell.color = get_color(map->grid[my][mx]);
				cell.size = MINIMAP_CELL_SIZE;
				draw_cell(minimap->img, cell);
			}
			my++;
		}
		mx++;
	}
}

void	draw_minimap_sprites(t_map *map, t_minimap *minimap)
{
	int		i;
	t_cell	sprite_cell;

	i = 0;
	while (i < map->sprite_count)
	{
		sprite_cell.px = (int)(map->sprites[i].x * MINIMAP_CELL_SIZE)
			- minimap->offset_x - MINIMAP_CELL_SIZE / 4;
		sprite_cell.py = (int)(map->sprites[i].y * MINIMAP_CELL_SIZE)
			- minimap->offset_y - MINIMAP_CELL_SIZE / 4;
		sprite_cell.size = MINIMAP_CELL_SIZE / 2;
		sprite_cell.color = MINIMAP_SPRITE_COLOR;
		draw_cell(minimap->img, sprite_cell);
		i++;
	}
}
