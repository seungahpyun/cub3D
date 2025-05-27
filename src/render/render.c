/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 21:47:09 by jianisong     #+#    #+#                 */
/*   Updated: 2025/05/23 15:31:55 by jianisong     ########   odam.nl         */
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

static void	clear_images(t_game *game)
{
	ft_memset(game->minimap.img->pixels, 0, MINIMAP_W * MINIMAP_H
		* sizeof(int32_t));
	ft_memset(game->img->pixels, 0, WIDTH * HEIGHT * sizeof(int32_t));
}

void	render(t_game *game)
{
	clear_images(game);
	update_rays(game);
	render_3d_projection(game);
	render_minimap(game);
}
