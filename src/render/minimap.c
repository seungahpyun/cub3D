/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/27 15:02:23 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	calculate_offset(t_player *player, t_minimap *minimap)
{
	int	w_px;
	int	w_py;
	int	s_px;
	int	s_py;

	w_px = (int)(player->x * MINIMAP_CELL_SIZE);
	w_py = (int)(player->y * MINIMAP_CELL_SIZE);
	s_px = MINIMAP_W / 2;
	s_py = MINIMAP_H / 2;
	minimap->offset_x = w_px - s_px;
	minimap->offset_y = w_py - s_py;
}

/**
 * Draws minimap grid showing walls and floor around player:
 * 1. Iterates through all map cells
 * 2. For each valid cell, calculates screen position using offset
 * 3. Draws cell with appropriate color based on map content
 */
static void	draw_minimap_grid(t_map *map, t_minimap *minimap)
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
			if (is_valid_point(map, mx, my))
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

/**
 * Draws rays on minimap from the player:
 * 1. Calculate the ray angle and distiance to get hit point of ray
 * 2. Map map_corrdinates to minimap image position
 * 3. Draw the line on the minimap buffer
 */
static void	draw_minimap_rays(t_ray_data *rays, t_minimap *minimap)
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
		ray_angle = rays[i].angle;
		dist = rays[i].dist;
		end.x = start.x + cos(ray_angle) * dist * MINIMAP_CELL_SIZE;
		end.y = start.y - sin(ray_angle) * dist * MINIMAP_CELL_SIZE;
		draw_line(minimap->img, start, end, MINIMAP_RAY_COLOR);
		i++;
	}
}

static void	draw_minimap_player(t_player *player, t_minimap *minimap)
{
	t_cell	player_cell;
	t_point	player_start;
	t_point	player_end;

	player_cell.size = MINIMAP_CELL_SIZE / 4;
	player_cell.px = MINIMAP_W / 2 - player_cell.size / 2;
	player_cell.py = MINIMAP_H / 2 - player_cell.size / 2;
	player_cell.color = MINIMAP_PLAYER_COLOR;
	draw_cell(minimap->img, player_cell);
	player_start.x = MINIMAP_W / 2;
	player_start.y = MINIMAP_H / 2;
	player_end.x = player_start.x + cos(player->angle) * MINIMAP_CELL_SIZE;
	player_end.y = player_start.y - sin(player->angle) * MINIMAP_CELL_SIZE;
	draw_line(minimap->img, player_start, player_end, RED);
}

void	render_minimap(t_game *game)
{
	game->minimap.img = mlx_new_image(game->mlx, MINIMAP_W, MINIMAP_H);
	if (!game->minimap.img)
		ft_mlx_error(game);
	ft_memset(game->minimap.img->pixels, 0, MINIMAP_W * MINIMAP_H
		* sizeof(int32_t));
	calculate_offset(&game->player, &game->minimap);
	draw_minimap_grid(&game->map, &game->minimap);
	draw_minimap_rays(game->rays, &game->minimap);
	draw_minimap_player(&game->player, &game->minimap);
	if (mlx_image_to_window(game->mlx, game->minimap.img, 0, 0) < 0)
		ft_mlx_error(game);
}
