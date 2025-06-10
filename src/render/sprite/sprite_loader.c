/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_loader.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 11:21:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/10 09:27:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "parser.h"

static bool	load_sprite_frame_from_path(mlx_t *mlx, t_sprite *sprite,
									const char *path, int frame)
{
	mlx_texture_t	*texture;

	if (!path)
		return (print_error("Sprite frame path is NULL", false));
	texture = mlx_load_png(path);
	if (!texture)
	{
		print_error_with_value("Failed to load sprite texture: ", path, false);
		return (false);
	}
	sprite->frames[frame] = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!sprite->frames[frame])
	{
		print_error_with_value("Failed to convert sprite texture: ", path,
			false);
		return (false);
	}
	return (true);
}

static void	cleanup_loaded_frames(mlx_t *mlx, t_sprite *sprite, int frame_count)
{
	int	i;

	i = 0;
	while (i < frame_count)
	{
		if (sprite->frames[i])
			mlx_delete_image(mlx, sprite->frames[i]);
		sprite->frames[i] = NULL;
		i++;
	}
}

static bool	validate_sprite_loading_params(t_sprite *sprite,
										t_animated_sprite_config *config)
{
	if (!sprite || !config)
		return (print_error("Invalid sprite or config", false));
	if (sprite->type != SPRITE_ANIMATED)
		return (print_error("Unknown sprite type", false));
	if (!is_valid_frame_count(config->frame_count))
		return (print_error("Invalid frame count", false));
	return (true);
}

static bool	load_sprite_frames(mlx_t *mlx, t_sprite *sprite,
								t_animated_sprite_config *config)
{
	int	frame;

	if (!validate_sprite_loading_params(sprite, config))
		return (false);
	frame = 0;
	while (frame < config->frame_count)
	{
		if (!load_sprite_frame_from_path(mlx, sprite,
				config->paths[frame], frame))
		{
			cleanup_loaded_frames(mlx, sprite, frame);
			return (false);
		}
		frame++;
	}
	return (true);
}

bool	load_all_sprites(t_game *game)
{
	int	i;

	if (game->map.sprite_count == 0)
		return (true);
	if (!validate_animated_sprite_config(&game->asset.animated_sprite))
	{
		ft_putendl_fd("Error: Map contains sprites"
			" but no ANIMATED configuration", 2);
		return (false);
	}
	i = 0;
	while (i < game->map.sprite_count)
	{
		if (!load_sprite_frames(game->mlx, &game->map.sprites[i],
				&game->asset.animated_sprite))
		{
			ft_putstr_fd("Error: Failed to load sprite frames for sprite ", 2);
			ft_putnbr_fd(i, 2);
			ft_putendl_fd("", 2);
			return (false);
		}
		i++;
	}
	return (true);
}
