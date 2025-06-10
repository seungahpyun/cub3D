/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 11:22:50 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/06 19:02:58 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	is_within_boundary(int x, int y, int height, int width)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return (false);
	return (true);
}

bool	is_valid_map_coord(t_map *map, int mx, int my)
{
	if (!is_within_boundary(mx, my, map->height, map->width))
		return (false);
	if (mx >= (int)ft_strlen(map->grid[my]))
		return (false);
	return (true);
}
