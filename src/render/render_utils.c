/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/14 11:26:04 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_cell(mlx_image_t *img, int px, int py, int cell_size, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < cell_size)
	{
		y = 0;
		while (y < cell_size)
		{
			mlx_put_pixel(img, px + x, py + y, color);
			y++;
		}
		x++;
	}
}

int	calculate_cell_size(int map_width, int map_height)
{
	float	cell_w;
	float	cell_h;
	int		cell_size;

	cell_w = (float)MINIMAP_W / map_width;
	cell_h = (float)MINIMAP_H / map_height;
	cell_size = (int)fminf(cell_w, cell_h);
	if (cell_size < 1)
		cell_size = 1;
	return (cell_size);
}
