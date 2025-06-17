/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_door.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/17 11:19:07 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/17 11:19:33 by jsong         ########   odam.nl         */
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
	door_rec->height = MINIMAP_CELL_SIZE * (1 - door->openness) + (door_padding
			* 2);
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
	door_rec->width = MINIMAP_CELL_SIZE * (1 - door->openness) + (door_padding
			* 2);
	door_rec->height = door_size;
	door_rec->color = MINIMAP_DOOR_COLOR;
}

static void	draw_minimap_single_door(t_map *map, t_minimap *minimap, int mx,
		int my)
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

void	draw_minimap_doors(t_map *map, t_minimap *minimap)
{
	int	mx;
	int	my;

	mx = 0;
	if (!map->contains_door)
		return ;
	while (mx < map->width)
	{
		my = 0;
		while (my < map->height)
		{
			if (is_valid_map_coord(map, mx, my) && map->doors[my][mx].is_door)
			{
				draw_minimap_single_door(map, minimap, mx, my);
			}
			my++;
		}
		mx++;
	}
}
