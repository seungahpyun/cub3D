/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_grid.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:31:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/17 10:24:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	calculate_vertical_door_rect(t_door *door, t_minimap *minimap,
		t_rect *door_rec)
{
	int		door_size;
	int		door_padding;
	double	door_x;

	door_size = MINIMAP_CELL_SIZE / 3;
	door_padding = 3;
	door_x = door->mx + 0.5;
	door_rec->px = door_x * MINIMAP_CELL_SIZE - door_size / 2
		- minimap->offset_x;
	door_rec->py = door->my * MINIMAP_CELL_SIZE - minimap->offset_y
		- door_padding;
	door_rec->width = door_size;
	door_rec->height = MINIMAP_CELL_SIZE * (1 - door->openness)
		+ (door_padding * 2);
	door_rec->color = MINIMAP_DOOR_COLOR;
}

static void	calculate_horizontal_door_rect(t_door *door, t_minimap *minimap,
		t_rect *door_rec)
{
	int		door_size;
	int		door_padding;
	double	door_y;

	door_size = MINIMAP_CELL_SIZE / 3;
	door_padding = 3;
	door_y = door->my + 0.5;
	door_rec->px = door->mx * MINIMAP_CELL_SIZE - minimap->offset_x
		- door_padding;
	door_rec->py = door_y * MINIMAP_CELL_SIZE - door_size / 2
		- minimap->offset_y;
	door_rec->width = MINIMAP_CELL_SIZE * (1 - door->openness)
		+ (door_padding * 2);
	door_rec->height = door_size;
	door_rec->color = MINIMAP_DOOR_COLOR;
}

static void	draw_minimap_door(t_map *map, t_minimap *minimap, int mx, int my)
{
	t_rect	door_rec;
	t_door	*door;

	door = &map->doors[my][mx];
	if (door->type == DOOR_VERTICAL)
		calculate_vertical_door_rect(door, minimap, &door_rec);
	else
		calculate_horizontal_door_rect(door, minimap, &door_rec);
	draw_rec(minimap->img, door_rec);
}

void draw_minimap_doors_only(t_map *map, t_minimap *minimap)
{
	int	mx;
	int	my;

	mx = 0;
	while (mx < map->width)
	{
		my = 0;
		while (my < map->height)
		{
			if (is_valid_map_coord(map, mx, my) && map->doors[my][mx].is_door)
			{
				draw_minimap_door(map, minimap, mx, my);
			}
			my++;
		}
		mx++;
	}
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
				// if (map->doors[my][mx].is_door)
				// 	draw_minimap_door(map, minimap, mx, my);
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
