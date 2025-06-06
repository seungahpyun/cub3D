/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_assets.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:55:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 18:52:49 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "render.h"

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

void	free_asset_images(t_asset *asset, mlx_t *mlx)
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

void	free_asset(t_asset *asset, mlx_t *mlx)
{
	if (!asset)
		return ;
	free_asset_paths(asset);
	free_asset_images(asset, mlx);
}
