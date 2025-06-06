/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_primitives.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 17:24:56 by jianisong     #+#    #+#                 */
/*   Updated: 2025/06/06 11:56:01 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(mlx_image_t *img, t_point start, t_point end, int color)
{
	int		steps;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;

	steps = fmax(abs(end.x - start.x), abs(end.y - start.y));
	x = start.x;
	y = start.y;
	x_inc = (end.x - start.x) / (float)steps;
	y_inc = (end.y - start.y) / (float)steps;
	while (steps-- >= 0)
	{
		if (is_within_boundary((int)x, (int)y, img->height, img->width))
			mlx_put_pixel(img, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
	}
}

void	draw_cell(mlx_image_t *img, t_cell cell)
{
	int	x;
	int	y;

	x = 0;
	while (x < cell.size)
	{
		y = 0;
		while (y < cell.size)
		{
			if (is_within_boundary(cell.px + x, cell.py + y, img->height,
					img->width))
				mlx_put_pixel(img, cell.px + x, cell.py + y, cell.color);
			y++;
		}
		x++;
	}
}
