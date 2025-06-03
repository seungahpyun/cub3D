/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 14:59:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/03 15:27:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	add_sprite_to_map(t_map *map, int x, int y, char sprite_char)
{
	t_sprite_type	type;

	if (map->sprite_count >= MAX_SPRITES)
	{
		ft_putendl_fd("Warning: Maximum sprite count reached", 2);
		return ;
	}
	if (sprite_char == 'T')
		type = SPRITE_TREE;
	else
		return ;
	map->sprites[map->sprite_count].x = x + 0.5;
	map->sprites[map->sprite_count].y = y + 0.5;
	map->sprites[map->sprite_count].type = type;
	map->sprites[map->sprite_count].current_frame = 0;
	map->sprites[map->sprite_count].last_frame_time = 0.0;
	map->sprites[map->sprite_count].distance = 0.0;
	map->sprite_count++;
}

void	parse_sprite_from_map(t_map *map)
{
	int	x;
	int	y;

	if (!map || !map->grid)
		return ;
	y = 0;
	while(y < map->height && map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_sprite_char(map->grid[y][x]))
			{
				add_sprite_to_map(map, x, y, map->grid[y][x]);
				map->grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
