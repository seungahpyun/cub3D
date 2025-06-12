/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 14:30:17 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/10 17:45:56 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	print_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	ft_putstr_fd("[map info]: \n", 1);
	while (i < map->height)
	{
		ft_putendl_fd(map->grid[i], 1);
		i++;
	}
	ft_putstr_fd("map_width is: ", 1);
	ft_putnbr_fd(map->width, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("map_height is: ", 1);
	ft_putnbr_fd(map->height, 1);
	ft_putstr_fd("\n", 1);
}

static void	print_single_door(t_door *door)
{
	if (!door)
		return ;
	printf("door_state is %d\n", door->state);
	printf("door_openness is %f\n", door->openness);
	printf("door_type is %d\n", door->type);
}

static void	print_doors(t_map *map)
{
	int	x;
	int	y;

	if (!map)
		return ;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (is_valid_map_coord(map, x, y))
		{
			if (map->doors[y][x].is_door)
			{
				printf("[Door info at (%d, %d)] : \n", y, x);
				print_single_door(&map->doors[y][x]);
			}
			x++;
		}
		y++;
	}
}

static void	print_player(t_player *player)
{
	if (!player)
		return ;
	ft_putstr_fd("[player info]: \n", 1);
	ft_putstr_fd("player_x is: ", 1);
	ft_putnbr_fd(player->x, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("player_y is: ", 1);
	ft_putnbr_fd(player->y, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("player_dir is: ", 1);
	ft_putchar_fd(player->dir, 1);
	ft_putstr_fd("\n", 1);
}

void	debug(t_game *game)
{
	print_map(&game->map);
	print_doors(&game->map);
	print_player(&game->player);
}
