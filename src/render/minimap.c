/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/23 14:06:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/**
 * Draws walls/floor on minimap around player:
 * 1. Calculate top-left starting grid position
 * 2. Iterate through MINIMAP_GRID x MINIMAP_GRID cells:
 *    a. Convert grid position to map coordinates
 *    b. Validate map coordinates
 *    c. If valid: draw scaled cell (MINIMAP_CELL_SIZE) at calculated
 *       screen position with color based on map cell type
 */
static void	draw_minimap_cell(t_game *game, int i, int j)
{
	 int		mx;
	 int		my;
	 t_cell	cell;
	 double	offset_x;
	 double	offset_y;

	 offset_x = game->player.x - (int)game->player.x;
	 offset_y = game->player.y - (int)game->player.y;
	 mx = (int)game->player.x - MINIMAP_RADIUS + i;
	 my = (int)game->player.y - MINIMAP_RADIUS + j;
	 if (is_valid_point(&game->map, mx, my))
	 {
		 cell.px = i * MINIMAP_CELL_SIZE - (int)(offset_x * MINIMAP_CELL_SIZE);
		 cell.py = j * MINIMAP_CELL_SIZE - (int)(offset_y * MINIMAP_CELL_SIZE);
		 cell.size = MINIMAP_CELL_SIZE;
		 cell.color = get_color(game->map.grid[my][mx]);
		 draw_cell(game->minimap.img, cell);
	 }
}

static void	draw_minimap_grid(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_GRID)
	{
		j = 0;
		while (j < MINIMAP_GRID)
		{
			draw_minimap_cell(game, i, j);
			j++;
		}
		i++;
	}
}

/**
 * Draws rays on minimap from the player:
 * 1. Calculate the ray angle and distiance to get hit point of ray
 * 2. Map map_corrdinates to minimap image position
 * 3. Draw the line on the minimap buffer
 */
static void	draw_minimap_rays(t_game *game)
{
	double	ray_angle;
	double	dist;
	t_point	start;
	t_point	end;
	int		i;

	start.x = MINIMAP_W / 2;
	start.y = MINIMAP_H / 2;
	i = 0;
	while (i < WIDTH)
	{
		ray_angle = game->rays[i].angle;
		dist = game->rays[i].dist;
		end.x = start.x + cos(ray_angle) * dist * MINIMAP_CELL_SIZE;
		end.y = start.y - sin(ray_angle) * dist * MINIMAP_CELL_SIZE;
		draw_line(game->minimap.img, start, end, MINIMAP_RAY_COLOR);
		i++;
	}
}

static void	draw_minimap_player(t_game *game)
{
	t_cell	player_cell;

	player_cell.px = MINIMAP_W / 2 - (MINIMAP_CELL_SIZE * 3 / 4) / 2;
	player_cell.py = MINIMAP_H / 2 - (MINIMAP_CELL_SIZE * 3 / 4) / 2;
	player_cell.size = MINIMAP_CELL_SIZE * 3 / 4;
	player_cell.color = MINIMAP_PLAYER_COLOR;
	draw_cell(game->minimap.img, player_cell);
}

void	render_minimap(t_game *game)
{
	if (!game->minimap.img)
	{
		game->minimap.img = mlx_new_image(game->mlx, MINIMAP_W, MINIMAP_H);
		if (!game->minimap.img)
			ft_mlx_error(game);
		if (mlx_image_to_window(game->mlx, game->minimap.img, 0, 0) < 0)
			ft_mlx_error(game);
	}
	ft_memset(game->minimap.img->pixels, 0, MINIMAP_W * MINIMAP_H
		* sizeof(int32_t));
	draw_minimap_grid(game);
	draw_minimap_rays(game);
	draw_minimap_player(game);
	if (mlx_image_to_window(game->mlx, game->minimap.img, 0, 0) < 0)
		ft_mlx_error(game);
}
