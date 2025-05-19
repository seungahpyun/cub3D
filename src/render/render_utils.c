/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/19 16:27:55 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_within_boundary(int mx, int my, int width, int height)
{
	return (mx >= 0 && my >= 0 && mx < width && my < height);
}

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

double	dir_to_angle(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'W')
		return (M_PI);
	if (c == 'S')
		return (3 * M_PI / 2);
	return (-1);
}

void	draw_line(mlx_image_t *img, t_point start, t_point end, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	x;
	float	y;
	float	x_inc;
	float	y_inc;
	int		draw_x;
	int		draw_y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = fmax(abs(dx), abs(dy));
	x = start.x;
	y = start.y;
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	for (int i = 0; i <= steps; i++)
	{
		draw_x = (int)x;
		draw_y = (int)y;
		if (is_within_boundary(draw_x, draw_y, img->width, img->height))
			mlx_put_pixel(img, draw_x, draw_y, color);
		x += x_inc;
		y += y_inc;
	}
}

bool	is_valid_point(t_game *game, int mx, int my)
{
	if (!is_within_boundary(mx, my, game->map_width, game->map_height))
		return (false);
	if (mx >= (int)ft_strlen(game->map[my]))
		return (false);
	return (true);
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
			if ((uint32_t)cell.px + x < img->width && (uint32_t)cell.py
				+ y < img->height)
				mlx_put_pixel(img, cell.px + x, cell.py + y, cell.color);
			y++;
		}
		x++;
	}
}

int	get_color(char c)
{
	if (c == '1')
		return (MINIMAP_WALL_COLOR);
	if (c == '0')
		return (MINIMAP_FLOOR_COLOR);
	if (c == ' ')
		return (MINIMAP_EMPTY_COLOR);
	return (MINIMAP_PLAYER_COLOR);
}

// int	calculate_cell_size(int map_width, int map_height)
// {
// 	float	cell_w;
// 	float	cell_h;
// 	int		cell_size;

// 	cell_w = (float)MINIMAP_W / map_width;
// 	cell_h = (float)MINIMAP_H / map_height;
// 	cell_size = (int)fminf(cell_w, cell_h);
// 	if (cell_size < 1)
// 		cell_size = 1;
// 	return (cell_size);
// }

// static void	draw_player(t_game *game)
// {
// 	int	player_px;
// 	int	player_py;
// 	int	cell_size;
// 	int	player_size;

// 	cell_size = game->minimap.cell_size;
// 	player_size = cell_size / 3;
// 	if (player_size < 1)
// 		player_size = 1;
// 	player_px = game->player_x * cell_size + player_size;
// 	player_py = game->player_y * cell_size + player_size;
// 	draw_cell(game->minimap.img, player_px, player_py, player_size,
// 		MINIMAP_PLAYER_COLOR);
// }