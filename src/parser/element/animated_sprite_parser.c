/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animated_sprite_parser.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 19:32:30 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 20:26:33 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	validate_animated_texture_path(const char *path)
{
	if (!path)
		return (ft_putendl_fd("Error: Animated sprite path is NULL", 2), -1);
	if (ft_strlen(path) == 0)
		return (ft_putendl_fd("Error: Animated sprite path is empty", 2), -1);
	if (!check_texture_extension(path))
		return (ft_putendl_fd("Error: Invalid \
            animated sprite texture extension", 2), -1);
	if (!check_texture_path(path))
		return (ft_putendl_fd("Error: Cannot access \
            animated sprite texture file", 2), -1);
	return (0);
}

static int	validate_animated_sprite_format(char **split)
{
	if (!split[0] || !split[1] || split[2])
		return (ft_putendl_fd("Error: Invalid ANIMATED format", 2), -1);
	return (0);
}

static int	add_sprite_path_to_config(t_animated_sprite_config *config,
								const char *path)
{
	char	*new_path;

	if (config->frame_count >= MAX_SPRITE_FRAMES)
		return (ft_putendl_fd("Error: Too many animated sprite frames", 2),
			-1);
	new_path = ft_strdup(path);
	if (!new_path)
		return (-1);
	config->paths[config->frame_count++] = new_path;
	return (0);
}

int	parse_animated_sprite(char *line, t_animated_sprite_config *config)
{
	char	*trimmed;
	char	**split;
	int		ret;

	trimmed = ft_trim_and_compact(line);
	if (!trimmed)
		return (-1);
	split = ft_split(trimmed, ' ');
	free(trimmed);
	if (!split)
		return (-1);
	if (validate_animated_sprite_format(split) != 0)
		return (ft_free_strarr(split), -1);
	ret = validate_animated_texture_path(split[1]);
	if (ret == 0)
		ret = add_sprite_path_to_config(config, split[1]);
	ft_free_strarr(split);
	return (ret);
}

bool	validate_animated_sprite_config(t_animated_sprite_config *config)
{
	if (!config)
		return (false);
	if (!is_valid_frame_count(config->frame_count))
	{
		ft_putstr_fd("Error: Animated sprite frame count must be between ", 2);
		ft_putnbr_fd(MIN_SPRITE_FRAMES, 2);
		ft_putstr_fd(" and ", 2);
		ft_putnbr_fd(MAX_SPRITE_FRAMES, 2);
		ft_putendl_fd("", 2);
		return (false);
	}
	return (true);
}
