/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/16 16:50:23 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_cell(mlx_image_t *img, t_cell cell);
int			get_color(char c);
int			dir_to_degree(char c);
double		degree_to_radian(double degree);

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

	mx = game->player_x - MINIMAP_RADIUS + i;
	my = game->player_y - MINIMAP_RADIUS + j;
	if (is_valid_point(game, mx, my))
	{
		cell.px = i * MINIMAP_CELL_SIZE;
		cell.py = j * MINIMAP_CELL_SIZE;
		cell.size = MINIMAP_CELL_SIZE;
		cell.color = get_color(game->map[my][mx]);
		draw_cell(game->minimap, cell);
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
 * 1. Calculate the ray hit point
 * 2. Map map_corrdinates to minimap image position
 * 3. Draw the line on the minimap buffer
 */
static void	draw_minimap_ray(t_game *game)
{
	double	ray_angle;
	int		player_angle;
	double	dist;
	double	hit_x;
	double	hit_y;
	int		sx;
	int		sy;
	int		center_x;
	int		center_y;

	center_x = MINIMAP_W / 2;
	center_y = MINIMAP_H / 2;
	player_angle = dir_to_degree(game->player_dir);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		ray_angle = degree_to_radian(player_angle - FOV / 2 + FOV * i
				/ NUM_RAYS);
		dist = cast_ray(game, ray_angle);
		hit_x = game->player_x + cos(ray_angle) * dist;
		hit_y = game->player_y + sin(ray_angle) * dist;
		sx = center_x + (hit_x - game->player_x) * MINIMAP_CELL_SIZE;
		sy = center_y + (hit_y - game->player_y) * MINIMAP_CELL_SIZE;
		draw_line(game->minimap, center_x, center_y, sx, sy, 0xFF000000);
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
	draw_minimap_grid(game);
	draw_minimap_ray(game);
	if (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0)
		ft_mlx_error(game);
}
