/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap_grid.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 15:10:07 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/06 15:38:39 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	t_cell	cell;

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
				cell.size = MINIMAP_CELL_SIZE;
				draw_cell(minimap->img, cell);
			}
			my++;
		}
		mx++;
	}
}

void	draw_minimap_door(void)
