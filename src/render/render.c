/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 21:47:09 by jianisong     #+#    #+#                 */
/*   Updated: 2025/05/26 10:43:53 by spyun         ########   odam.nl         */
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
	t_game			*game;
	static double	last_time = 0;
	double			current_time;

	game = (t_game *)param;
	current_time = mlx_get_time();
	if (current_time - last_time > 0.016)
	{
		update_rays(game);
		render_minimap(game);
		last_time = current_time;
	}
}

void	render(t_game *game)
{
	update_rays(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
}
