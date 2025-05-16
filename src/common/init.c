/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 15:59:19 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/16 11:16:01 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		ft_mlx_error(game);
}

static void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->dir = '\0';
}

static void	init_asset(t_asset *asset)
{
	asset->no_path = NULL;
	asset->so_path = NULL;
	asset->we_path = NULL;
	asset->ea_path = NULL;
	asset->floor.r = -1;
	asset->floor.g = -1;
	asset->floor.b = -1;
	asset->ceiling.r = -1;
	asset->ceiling.g = -1;
	asset->ceiling.b = -1;
	asset->no_img = NULL;
	asset->so_img = NULL;
	asset->we_img = NULL;
	asset->ea_img = NULL;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
}

void	init_game_state(t_game *game)
{
	game->mlx = NULL;
	init_asset(&game->asset);
	init_player(&game->player);
	init_map(&game->map);
}
