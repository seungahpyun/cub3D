/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   animated_sprite_parser.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 19:32:30 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 19:41:19 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_valid_frame_count(int count)
{
	return (count >= MIN_SPRITE_FRAMES && count <= MAX_SPRITE_FRAMES);
}

static int	validate_animated_texture_path(const char *path)
{
	if (!path)
		return (ft_putendl_fd("Error: Animated sprite path is NULL", 2), -1);
	if (ft_strlen(path) == 0)
		return (ft_putendl_fd("Error: Animated sprite path is empty", 2), -1);
	if (!check_texture_extension(path))
		return (ft_putendl_fd("Error: Invalid animated sprite texture extension", 2), -1);
	if (!check_texture_path(path))
		return (ft_putendl_fd("Error: Cannot access animated sprite texture file", 2), -1);
	return (0);
}

int	parse_animated_sprite(char *line, t_animated_sprite_config *config)
{
	char	*trimmed;
	char	**split;
	char	*path;
	int		ret;

	trimmed = ft_trim_and_compact(line);
	if (!trimmed)
		return (-1);
	split = ft_split(trimmed, ' ');
	free(trimmed);
	if (!split)
		return (-1);
	if (!split[0] || !split[1] || split[2])
		return (ft_free_strarr(split), ft_putendl_fd("Error: Invalid ANIMATED format", 2), -1);
	if (config->frame_count >= MAX_SPRITE_FRAMES)
		return (ft_free_strarr(split), ft_putendl_fd("Error: Too many animated sprite frames", 2), -1);
	ret = validate_animated_texture_path(split[1]);
	if (ret == 0)
	{
		path = ft_strdup(split[1]);
		if (!path)
			ret = -1;
		else
			config->paths[config->frame_count++] = path;
	}
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
