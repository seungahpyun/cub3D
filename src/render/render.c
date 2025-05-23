/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 21:47:09 by jianisong     #+#    #+#                 */
/*   Updated: 2025/05/23 13:44:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	update_rays(t_game *game)
{
	t_ray	ray;
	int		i;
	double	ray_angle;

	i = 0;
	while (i < WIDTH)
	{
		ray_angle = game->player.angle + game->rays[i].angle_offset;
		game->rays[i].angle = ray_angle;
		init_ray(&game->player, ray_angle, &ray);
		game->rays[i].dist = cast_ray(&game->map, &ray);
		i++;
	}
}

static void	game_loop(void *param)
{
	t_game	*game;
	t_cell	cell;

	game = (t_game *)param;
	update_rays(game);
	render_minimap(game);
	cell.px = MINIMAP_W / 2 - (MINIMAP_CELL_SIZE * 3 / 4) / 2;
	cell.py = MINIMAP_H / 2 - (MINIMAP_CELL_SIZE * 3 / 4) / 2;
	cell.size = MINIMAP_CELL_SIZE * 3 / 4;
	cell.color = MINIMAP_PLAYER_COLOR;
	draw_cell(game->minimap.img, cell);
}

void	render(t_game *game)
{
	update_rays(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
}
