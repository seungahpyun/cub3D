/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 11:34:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 15:26:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

static void	free_asset_paths(t_asset *asset)
{
	if (asset->no_path)
		free(asset->no_path);
	if (asset->so_path)
		free(asset->so_path);
	if (asset->we_path)
		free(asset->we_path);
	if (asset->ea_path)
		free(asset->ea_path);
	asset->no_path = NULL;
	asset->so_path = NULL;
	asset->we_path = NULL;
	asset->ea_path = NULL;
}

static void	free_asset_images(t_asset *asset, mlx_t *mlx)
{
	if (mlx && asset->no_img)
		mlx_delete_image(mlx, asset->no_img);
	if (mlx && asset->so_img)
		mlx_delete_image(mlx, asset->so_img);
	if (mlx && asset->we_img)
		mlx_delete_image(mlx, asset->we_img);
	if (mlx && asset->ea_img)
		mlx_delete_image(mlx, asset->ea_img);
	asset->no_img = NULL;
	asset->so_img = NULL;
	asset->we_img = NULL;
	asset->ea_img = NULL;
}

static void	free_asset(t_asset *asset, mlx_t *mlx)
{
	if (!asset)
		return ;
	free_asset_paths(asset);
	free_asset_images(asset, mlx);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	free_asset(&game->asset, game->mlx);
}
