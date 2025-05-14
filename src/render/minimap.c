/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/14 12:58:13 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void		draw_cell(mlx_image_t *img, int px, int py, int cell_size,
// 				int color);

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
static int	is_within_map(int mx, int my, int map_width, int map_height)
{
	return (mx >= 0 && my >= 0 && mx < map_width && my < map_height);
}

/**
 * Function to draw walls:
 * 1. Calculate how many cells can be seen in each direction from player
 * 2. For each cell position relative to player:
 * 		if cell is within map boundary:
 * 			calculate screen coordinate
 * 			draw corresponding cell type (wall/floor)
 */
static void	draw_walls(t_game *game)
{
	int	sx;
	int	sy;
	int	cell_size;
	int	offset_x;
	int	offset_y;
	int	mx;
	int	my;
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	cell_size = MINIMAP_CELL_SIZE;
	offset_x = 0.5 * (MINIMAP_W / MINIMAP_CELL_SIZE - 1);
	offset_y = 0.5 * (MINIMAP_H / MINIMAP_CELL_SIZE - 1);
	start_x = game->player_x - offset_x;
	start_y = game->player_y - offset_y;
	i = 0;
	while (i < MINIMAP_W / MINIMAP_CELL_SIZE)
	{
		j = 0;
		while (j < MINIMAP_H / MINIMAP_CELL_SIZE)
		{
			mx = start_x + i;
			my = start_y + j;
			if (is_within_map(mx, my, game->map_width, game->map_height))
			{
				sx = i * cell_size;
				sy = j * cell_size;
				if (game->map[my][mx] == '1')
					draw_cell(game->minimap.img, sx, sy, cell_size,
						MINIMAP_WALL_COLOR);
				else if (game->map[my][mx] == '0')
					draw_cell(game->minimap.img, sx, sy, cell_size,
						MINIMAP_FLOOR_COLOR);
				else
					draw_cell(game->minimap.img, sx, sy, cell_size,
						MINIMAP_PLAYER_COLOR);
			}
			j++;
		}
		i++;
	}
}

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
	// game->minimap.cell_size = calculate_cell_size(game->map_width,
	// 		game->map_height);
}

void	render_minimap(t_game *game)
{
	init_minimap(game);
	draw_walls(game);
	// draw_player(game);
	if (mlx_image_to_window(game->mlx, game->minimap.img, 0, 0) < 0)
		ft_mlx_error(game);
}
