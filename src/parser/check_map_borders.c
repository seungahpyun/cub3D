/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_borders.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/13 11:42:12 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 11:46:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_map_borders(char **map, t_game *game)
{
	int	x;
	int	y;
	int	last_row;

	last_row = game->map_height - 1;
	y = 0;
	while (y <= last_row)
	{
		if (y == 0 || y == last_row)
		{
			x = 0;
			while (map[y][x])
			{
				if (map[y][x] != '1' && map[y][x] != ' ')
				{
					ft_putendl_fd("Error: Map border not closed", 2);
					return (false);
				}
				x++;
			}
		}
		y++;
	}
	y = 0;
	while (y <= last_row)
	{
		x = 0;
		while (map[y][x])
		{
			if (x == 0 || x == (int)ft_strlen(map[y]) - 1)
			{
				if (map[y][x] != '1' && map[y][x] != ' ')
				{
					ft_putendl_fd("Error: Map border not closed", 2);
					return (false);
				}
			}
			x++;
		}
		y++;
	}
	return (true);
}
