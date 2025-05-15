/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/15 22:48:43 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		is_valid_point(char **map, int mx, int my, int map_width,
				int map_height);

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
			if ((uint32_t)px + x < img->width && (uint32_t)py + y < img->height)
				mlx_put_pixel(img, px + x, py + y, color);
			y++;
		}
		x++;
	}
}

static int	get_color(char c)
{
	if (c == '1')
		return (MINIMAP_WALL_COLOR);
	if (c == '0')
		return (MINIMAP_FLOOR_COLOR);
	if (c == ' ')
		return (MINIMAP_EMPTY_COLOR);
	return (MINIMAP_PLAYER_COLOR);
}

/**
 * Draws walls/floor on minimap around player:
 * 1. Calculate top-left starting grid position
 * 2. Iterate through MINIMAP_GRID x MINIMAP_GRID cells:
 *    a. Convert grid position to map coordinates
 *    b. Validate map coordinates
 *    c. If valid: draw scaled cell (MINIMAP_CELL_SIZE) at calculated
 *       screen position with color based on map cell type
 */
static void	draw_walls(t_game *game)
{
	int	mx;
	int	my;
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = game->player_x - MINIMAP_RADIUS;
	start_y = game->player_y - MINIMAP_RADIUS;
	i = -1;
	while (++i < MINIMAP_GRID)
	{
		j = -1;
		while (++j < MINIMAP_GRID)
		{
			mx = start_x + i;
			my = start_y + j;
			if (is_valid_point(game->map, mx, my, game->map_width,
					game->map_height))
				draw_cell(game->minimap, i * MINIMAP_CELL_SIZE, j
					* MINIMAP_CELL_SIZE, MINIMAP_CELL_SIZE,
					get_color(game->map[my][mx]));
		}
	}
}

void	render_minimap(t_game *game)
{
	game->minimap = mlx_new_image(game->mlx, MINIMAP_W, MINIMAP_H);
	if (!game->minimap)
		ft_mlx_error(game);
	// Set minimap background as transparent
	ft_memset(game->minimap->pixels, 0, MINIMAP_W * MINIMAP_H
		* sizeof(int32_t));
	draw_walls(game);
	if (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0)
		ft_mlx_error(game);
}
