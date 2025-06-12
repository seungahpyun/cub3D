/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_controller.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jianisong <jianisong@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/12 10:38:24 by jianisong     #+#    #+#                 */
/*   Updated: 2025/06/12 10:50:37 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	handle_door_interaction(t_map *map, t_player *player)
{
	int	front_x;
	int	front_y;
	int	current_state;

	front_x = (int)(player->x + cos(player->angle) * 1.0);
	front_y = (int)(player->y - sin(player->angle) * 1.0);
	if (!is_door(map, front_x, front_y))
		return ;
	current_state = map->doors[front_y][front_x].state;
	if (current_state == DOOR_CLOSED)
		map->doors[front_y][front_x].state = DOOR_OPENING;
	else if (current_state == DOOR_OPEN)
		map->doors[front_y][front_x].state = DOOR_CLOSING;
	return ;
}
