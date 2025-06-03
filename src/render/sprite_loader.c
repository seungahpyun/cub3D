/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_loader.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 11:21:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/03 16:21:55 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static char	*create_sprite_path(t_sprite_type type, int frame)
{
	char	*path;
	char	*frame_str;
	char	*temp;

	frame_str = ft_itoa(frame);
	if (!frame_str)
		return (NULL);
	if (type == SPRITE_TREE)
	{
		temp = ft_strjoin("textures/tree/tree0", frame_str);
		if (!temp)
			return (free(frame_str), NULL);
		path = ft_strjoin(temp, ".png");
		free(temp);
	}
	else
		path = NULL;
	free(frame_str);
	return (path);
}

static bool	load_sprite_frame(mlx_t *mlx, t_sprite *sprite, int frame)
{
	char			*path;
	mlx_texture_t	*texture;

	path = create_sprite_path(sprite->type, frame);
	if (!path)
		return (print_error("Failed to create sprite path", false));
	texture = mlx_load_png(path);
	if (!texture)
	{
		print_error_with_value("Failed to load sprite texture: ", path, false);
		free(path);
		return (false);
	}
	sprite->frames[frame] = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!sprite->frames[frame])
	{
		print_error_with_value("Failed to convert sprite texture: ", path,
			false);
		free(path);
		return (false);
	}
	free(path);
	return (true);
}

static bool	load_sprite_frames(mlx_t *mlx, t_sprite *sprite)
{
	int	frame;
	int	max_frames;

	if (sprite->type == SPRITE_TREE)
		max_frames = TREE_FRAMES;
	else
		return (print_error("Unknown sprite type", false));
	frame = 0;
	while (frame < max_frames)
	{
		if (!load_sprite_frame(mlx, sprite, frame))
		{
			while (frame > 0)
			{
				frame--;
				if (sprite->frames[frame])
					mlx_delete_image(mlx, sprite->frames[frame]);
				sprite->frames[frame] = NULL;
			}
			return (false);
		}
		frame++;
	}
	return (true);
}

bool	load_all_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.sprite_count)
	{
		if (!load_sprite_frames(game->mlx, &game->map.sprites[i]))
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

void	free_sprite_frames(mlx_t *mlx, t_sprite *sprite)
{
	int	frame;
	int	max_frames;

	if (sprite->type == SPRITE_TREE)
		max_frames = TREE_FRAMES;
	else
		return ;
	frame = 0;
	while (frame < max_frames)
	{
		if (sprite->frames[frame])
		{
			mlx_delete_image(mlx, sprite->frames[frame]);
			sprite->frames[frame] = NULL;
		}
		frame++;
	}
}

void	free_all_sprites(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.sprite_count)
	{
		free_sprite_frames(game->mlx, &game->map.sprites[i]);
		i++;
	}
}
