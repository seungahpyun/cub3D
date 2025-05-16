/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/16 14:06:03 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_radian(double degree)
{
	return (degree * M_PI / 180);
}

int	dir_to_degree(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (90);
	if (c == 'W')
		return (180);
	if (c == 'S')
		return (270);
	return (-1);
}

static int	is_within_map(int mx, int my, int map_width, int map_height)
{
	return (mx >= 0 && my >= 0 && mx < map_width && my < map_height);
}

bool	is_valid_point(t_game *game, int mx, int my)
{
	if (!is_within_map(mx, my, game->map_width, game->map_height))
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