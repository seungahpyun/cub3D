/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 15:17:24 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/22 22:08:53 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static double	dir_to_angle(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'N')
		return (M_PI / 2);
	if (c == 'W')
		return (M_PI);
	if (c == 'S')
		return (3 * M_PI / 2);
	return (-1);
}

static void	init_rays_offset(t_ray_data *rays)
{
	int		i;
	double	step;

	i = 0;
	step = FOV / (WIDTH - 1);
	while (i < WIDTH)
	{
		rays[i].angle_offset = degree_to_radian(-0.5 * FOV + step * i);
		i++;
	}
}

void	setup_for_raycasting(t_game *game)
{
	game->player.x = game->player.x + 0.5;
	game->player.y = game->player.y + 0.5;
	game->player.angle = dir_to_angle(game->player.dir);
	init_rays_offset(game->rays);
}
