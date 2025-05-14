/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 11:34:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/14 16:09:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	free_asset(t_asset *asset)
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
	if (asset->no_img)
		mlx_delete_image(asset->no_img);
	if (asset->so_img)
		mlx_delete_image(asset->so_img);
	if (asset->we_img)
		mlx_delete_image(asset->we_img);
	if (asset->ea_img)
		mlx_delete_image(asset->ea_img);
	asset->no_path = NULL;
	asset->so_path = NULL;
	asset->we_path = NULL;
	asset->ea_path = NULL;
	asset->no_img = NULL;
	asset->so_img = NULL;
	asset->we_img = NULL;
	asset->ea_img = NULL;
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	free_asset(&game->asset);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
