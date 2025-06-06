/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_player_minimap.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 19:59:57 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 20:10:27 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	init_player(t_player *player)
{
	player->x = -1.0;
	player->y = -1.0;
	player->dir = '\0';
	player->angle = -1.0;
}

void	init_minimap(t_minimap *minimap)
{
	minimap->offset_x = 0;
	minimap->offset_y = 0;
	minimap->img = NULL;
}
