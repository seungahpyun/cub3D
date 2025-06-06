/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 11:34:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 16:17:52 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "render.h"

static void	free_2d_array(void **arr, int rows)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < rows)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map(t_map *map)
{
	int	rows;

	if (!map)
		return ;
	rows = map->height;
	if (rows <= 0)
		return ;
	free_2d_array((void **)map->grid, rows);
	map->grid = NULL;
	free_2d_array((void **)map->doors, rows);
	map->doors = NULL;
}

static void	free_asset_paths(t_asset *asset)
{
	if (!asset)
		return ;
	if (asset->no_path)
		free(asset->no_path);
	if (asset->so_path)
		free(asset->so_path);
	if (asset->we_path)
		free(asset->we_path);
	if (asset->ea_path)
		free(asset->ea_path);
	if (asset->door_path)
		free(asset->door_path);
	asset->no_path = NULL;
	asset->so_path = NULL;
	asset->we_path = NULL;
	asset->ea_path = NULL;
	asset->door_path = NULL;
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	free_asset_paths(&game->asset);
	if (game->mlx)
		free_textures(game);
	if (game->mlx && game->minimap.img)
	{
		mlx_delete_image(game->mlx, game->minimap.img);
		game->minimap.img = NULL;
	}
}
