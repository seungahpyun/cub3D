/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/12 17:57:38 by jsong         ########   odam.nl         */
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

static int	calculate_cell_size(t_game *game)
{
	float	cell_w;
	float	cell_h;
	int		cell_size;

	cell_w = (float)MINIMAP_W / game->map_width;
	ft_putnbr_fd(game->map_width, STDOUT_FILENO);
	game->map_height = 6;
	cell_h = (float)MINIMAP_H / game->map_height;
	cell_size = (int)fminf(cell_w, cell_h);
	return (cell_size);
}

void	render_minimap(t_game *game)
{
	int	cell_size;

	game->minimap = mlx_new_image(game->mlx, MINIMAP_W, MINIMAP_H);
	if (!game->minimap)
		ft_mlx_error(game);
	// Set every pixel to white
	ft_memset(game->minimap->pixels, 255, game->minimap->width
		* game->minimap->height * sizeof(int32_t));
	cell_size = calculate_cell_size(game);
	draw_cell(game->minimap, 0, 0, cell_size, MINIMAP_WALL_COLOR);
	if (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0)
		ft_mlx_error(game);
}
