/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_grid.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:31:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/10 17:45:22 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	draw_minimap_door(t_map *map, t_minimap *minimap, int mx, int my)
{
	int		door_size;
	t_rect	door_rec;
	double	door_x;
	double	door_y;

	door_x = mx + 0.5;
	door_y = my + 0.5;
	door_size = MINIMAP_CELL_SIZE / 3;
	if (map->doors[my][mx].type == DOOR_VERTICAL)
	{
		door_rec.px = door_x * MINIMAP_CELL_SIZE - door_size / 2
			- minimap->offset_x;
		door_rec.py = my * MINIMAP_CELL_SIZE - minimap->offset_y;
		door_rec.width = door_size;
		door_rec.height = MINIMAP_CELL_SIZE * (1 - map->doors[my][mx].openness);
		door_rec.color = MINIMAP_DOOR_COLOR;
	}
	else
	{
		door_rec.px = mx * MINIMAP_CELL_SIZE - minimap->offset_x;
		door_rec.py = door_y * MINIMAP_CELL_SIZE - door_size / 2
			- minimap->offset_y;
		door_rec.width = MINIMAP_CELL_SIZE * (1 - map->doors[my][mx].openness);
		door_rec.height = door_size;
		door_rec.color = MINIMAP_DOOR_COLOR;
		;
	}
	draw_rec(minimap->img, door_rec);
}

/**
 * Draws minimap grid showing walls and floor around player:
 * 1. Iterates through all map cells
 * 2. For each valid cell, calculates screen position using offset
 * 3. Draws cell with appropriate color based on map content
 */
void	draw_minimap_grid(t_map *map, t_minimap *minimap)
{
	int		mx;
	int		my;
	t_rect	cell;

	mx = 0;
	while (mx < map->width)
	{
		my = 0;
		while (my < map->height)
		{
			if (is_valid_map_coord(map, mx, my))
			{
				cell.px = mx * MINIMAP_CELL_SIZE - minimap->offset_x;
				cell.py = my * MINIMAP_CELL_SIZE - minimap->offset_y;
				cell.color = get_color(map->grid[my][mx]);
				cell.width = MINIMAP_CELL_SIZE;
				cell.height = cell.width;
				draw_rec(minimap->img, cell);
				if (map->doors[my][mx].is_door)
					draw_minimap_door(map, minimap, mx, my);
			}
			my++;
		}
		mx++;
	}
}

void	draw_minimap_sprites(t_map *map, t_minimap *minimap)
{
	int		i;
	t_rect	sprite_cell;

	i = 0;
	while (i < map->sprite_count)
	{
		sprite_cell.px = (int)(map->sprites[i].x * MINIMAP_CELL_SIZE)
			- minimap->offset_x - MINIMAP_CELL_SIZE / 4;
		sprite_cell.py = (int)(map->sprites[i].y * MINIMAP_CELL_SIZE)
			- minimap->offset_y - MINIMAP_CELL_SIZE / 4;
		sprite_cell.width = MINIMAP_CELL_SIZE / 2;
		sprite_cell.height = sprite_cell.width;
		sprite_cell.color = MINIMAP_SPRITE_COLOR;
		draw_rec(minimap->img, sprite_cell);
		i++;
	}
}
