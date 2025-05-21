/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/21 15:17:24 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/21 15:24:03 by jsong         ########   odam.nl         */
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

void	setup_player_for_raycasting(t_player *player)
{
	player->x = player->x + 0.5;
	player->y = player->y + 0.5;
	player->angle = dir_to_angle(player->dir);
}
