/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_player_minimap.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
<<<<<<< HEAD:src/common/init_components.c
/*   Created: 2025/05/19 10:25:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 16:17:30 by jsong         ########   odam.nl         */
=======
/*   Created: 2025/06/06 19:59:57 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 20:10:27 by seungah       ########   odam.nl         */
>>>>>>> main:src/common/core/init_player_minimap.c
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
<<<<<<< HEAD:src/common/init_components.c

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->doors = NULL;
	map->width = 0;
	map->height = 0;
}
=======
>>>>>>> main:src/common/core/init_player_minimap.c
