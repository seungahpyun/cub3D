/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 21:47:09 by jianisong     #+#    #+#                 */
/*   Updated: 2025/05/27 17:11:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	clear_main_image(t_game *game)
{
	if (game->img && game->img->pixels)
		ft_memset(game->img->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
	if (game->minimap.img && game->minimap.img->pixels)
		ft_memset(game->minimap.img->pixels, 0, MINIMAP_W * MINIMAP_H
			* sizeof(int32_t));
}

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

static void	render_frame(t_game *game)
{
	clear_main_image(game);
	update_rays(game);
	render_3d_projection(game);
	render_minimap(game);
}

static void	game_loop(void *param)
{
	t_game			*game;
	static double	last_time = 0;
	double			current_time;

	game = (t_game *)param;
	current_time = mlx_get_time();
	if (current_time - last_time >= 0.016)
	{
		render_frame(game);
		last_time = current_time;
	}
}

void	render(t_game *game)
{
	render_frame(game);
	mlx_loop_hook(game->mlx, &game_loop, game);
}
