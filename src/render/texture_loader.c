/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_loader.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/26 11:50:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/02 09:47:48 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static bool	load_single_texture(mlx_t *mlx, const char *path, mlx_image_t **img)
{
	mlx_texture_t *texture;

	if (!path || !*path)
		return (print_error("Texture path is empty or NULL.", false));
	texture = mlx_load_png(path);
	if (!texture)
		return (print_error_with_value("Failed to load texture.", path, false));
	*img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!*img)
		return (print_error_with_value("Failed to convert texture to image.", path, false));
	return (true);
}

static void cleanup_loaded_textures(t_asset *asset, mlx_t *mlx)
{
	if (asset->no_img)
	{
		mlx_delete_image(mlx, asset->no_img);
		asset->no_img = NULL;
	}
	if (asset->so_img)
	{
		mlx_delete_image(mlx, asset->so_img);
		asset->so_img = NULL;
	}
	if (asset->we_img)
	{
		mlx_delete_image(mlx, asset->we_img);
		asset->we_img = NULL;
	}
	if (asset->ea_img)
	{
		mlx_delete_image(mlx, asset->ea_img);
		asset->ea_img = NULL;
	}
}

bool	load_textures(t_game *game)
{
	t_asset *asset;
	mlx_t 	*mlx;

	asset = &game->asset;
	mlx = game->mlx;
	if (!load_single_texture(mlx, asset->no_path, &asset->no_img))
		return (cleanup_loaded_textures(asset, mlx), false);
	if (!load_single_texture(mlx, asset->so_path, &asset->so_img))
		return (cleanup_loaded_textures(asset, mlx), false);
	if (!load_single_texture(mlx, asset->we_path, &asset->we_img))
		return (cleanup_loaded_textures(asset, mlx), false);
	if (!load_single_texture(mlx, asset->ea_path, &asset->ea_img))
		return (cleanup_loaded_textures(asset, mlx), false);
	return (true);
}

void	free_textures(t_game *game)
{
	cleanup_loaded_textures(&game->asset, game->mlx);
}
