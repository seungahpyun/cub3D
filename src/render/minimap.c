/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/13 14:58:03 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_cell(mlx_image_t *img, int px, int py, int cell_size,
		int color)
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

static int	calculate_cell_size(int map_width, int map_height)
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

static void	draw_walls(t_game *game)
{
	int	mx;
	int	my;
	int	cell_size;

	mx = 0;
	my = 0;
	cell_size = game->minimap.cell_size;
	while (mx < game->map_width)
	{
		my = 0;
		while (my < game->map_height)
		{
			if (game->map[my][mx] == '1')
				draw_cell(game->minimap.img, mx * cell_size, my * cell_size,
					cell_size, MINIMAP_WALL_COLOR);
			else
				draw_cell(game->minimap.img, mx * cell_size, my * cell_size,
					cell_size, MINIMAP_FLOOR_COLOR);
			my++;
		}
		mx++;
	}
}

static void	draw_player(t_game *game)
{
	int	player_px;
	int	player_py;
	int	cell_size;
	int	player_size;

	cell_size = game->minimap.cell_size;
	player_size = cell_size / 3;
	if (player_size < 1)
		player_size = 1;
	player_px = game->player_x * cell_size + player_size;
	player_py = game->player_y * cell_size + player_size;
	draw_cell(game->minimap.img, player_px, player_py, player_size,
		MINIMAP_PLAYER_COLOR);
}

// TO DO: delete game->map_height = 6 when map_parse is done.
void	init_minimap(t_game *game)
{
	game->minimap.img = mlx_new_image(game->mlx, MINIMAP_W, MINIMAP_H);
	if (!game->minimap.img)
		ft_mlx_error(game);
	// Set minimap background as transparent
	ft_memset(game->minimap.img->pixels, 0, MINIMAP_W * MINIMAP_H
		* sizeof(int32_t));
	game->map_height = 6;
	game->minimap.cell_size = calculate_cell_size(game->map_width,
			game->map_height);
}

void	render_minimap(t_game *game)
{
	init_minimap(game);
	draw_walls(game);
	draw_player(game);
	if (mlx_image_to_window(game->mlx, game->minimap.img, 0, 0) < 0)
		ft_mlx_error(game);
}
