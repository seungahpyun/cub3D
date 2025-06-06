/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_parser.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 14:59:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 20:42:41 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_sprite_type	get_sprite_type(char sprite_char)
{
	if (sprite_char == 'A')
		return (SPRITE_ANIMATED);
	return (SPRITE_ANIMATED);
}


static void	setup_new_sprite(t_sprite *sprite, int x, int y,
							t_animated_sprite_config *config)
{
	sprite->x = x + 0.5;
	sprite->y = y + 0.5;
	sprite->type = get_sprite_type('A');
	sprite->current_frame = 0;
	sprite->last_frame_time = 0.0;
	sprite->distance = 0.0;
	sprite->frame_count = config->frame_count;
	init_sprite_frames(sprite);
}

static void	add_sprite_to_map(t_map *map, int x, int y,
							t_animated_sprite_config *config)
{
	if (map->sprite_count >= MAX_SPRITES)
	{
		ft_putendl_fd("Warning: Maximum sprite count reached", 2);
		return ;
	}
	setup_new_sprite(&map->sprites[map->sprite_count], x, y, config);
	map->sprite_count++;
}

void	parse_sprite_from_map(t_map *map, t_animated_sprite_config *config)
{
	int	x;
	int	y;

	if (!map || !map->grid || !config)
		return ;
	y = 0;
	while (y < map->height && map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_sprite_char(map->grid[y][x]))
			{
				add_sprite_to_map(map, x, y, config);
				map->grid[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
