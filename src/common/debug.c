/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 14:30:17 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/20 14:44:15 by jsong         ########   odam.nl         */
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
	print_player(&game->player);
}