/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_loader.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/26 11:50:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/11 17:43:43 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	load_single_texture(mlx_t *mlx, const char *path, mlx_image_t **img)
{
	mlx_texture_t	*texture;

	if (!path || !*path)
		return (print_error("Texture path is empty or NULL.", false));
	texture = mlx_load_png(path);
	if (!texture)
		return (print_error_with_value("Failed to load texture.", path, false));
	*img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!*img)
		return (print_error_with_value("Failed to convert texture to image.",
				path, false));
	return (true);
}

bool	load_textures(t_game *game)
{
	t_asset	*asset;
	mlx_t	*mlx;

	asset = &game->asset;
	mlx = game->mlx;
	if (!load_single_texture(mlx, asset->no_path, &asset->no_img))
		return (free_asset_images(asset, mlx), false);
	if (!load_single_texture(mlx, asset->so_path, &asset->so_img))
		return (free_asset_images(asset, mlx), false);
	if (!load_single_texture(mlx, asset->we_path, &asset->we_img))
		return (free_asset_images(asset, mlx), false);
	if (!load_single_texture(mlx, asset->ea_path, &asset->ea_img))
		return (free_asset_images(asset, mlx), false);
	if (map_contains_door(&game->map))
	{
		if (!load_single_texture(mlx, asset->door_path, &asset->door_img))
			return (free_asset_images(asset, mlx), false);
	}
	return (true);
}
