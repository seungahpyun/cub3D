/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_validator.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:20:25 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 11:21:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_map_extension(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL)
		return (false);
	if (ft_strcmp(dot, ".cub") != 0)
		return (false);
	return (true);
}

static bool	check_texture_extension(const char *path)
{
	const char	*dot;
	size_t		len;

	len = ft_strlen(path);
	if (len < 5)
	{
		ft_putstr_fd("Error: Texture file name is too short: ", 2);
		ft_putendl_fd((char *)path, 2);
		return (false);
	}
	dot = ft_strrchr(path, '.');
	if (!dot)
	{
		ft_putstr_fd("Error: Texture file has no extension: ", 2);
		ft_putendl_fd((char *)path, 2);
		return (false);
	}
	if (ft_strcmp(dot, ".png") != 0)
	{
		ft_putstr_fd("Error: Invalid texture file extension: ", 2);
		ft_putendl_fd((char *)path, 2);
		return (false);
	}
	return (true);
}

bool	check_texture_path(const char *path)
{
	int	fd;

	if (!path)
	{
		ft_putendl_fd("Error: Texture path is NULL", 2);
		return (false);
	}
	if (ft_strlen(path) == 0)
	{
		ft_putendl_fd("Error: Texture path is empty", 2);
		return (false);
	}
	if (!check_texture_extension(path))
		return (false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Cannot open texture file: ", 2);
		ft_putendl_fd((char *)path, 2);
		return (false);
	}
	close(fd);
	return (true);
}

bool	check_color_value(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putendl_fd("Error: Invalid color value", 2);
		return (false);
	}
	return (true);
}
