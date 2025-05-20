/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_checker.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:20:25 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 15:18:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_texture_path(const char *path)
{
	int		fd;
	char	*trimmed_path;

	if (!path)
		return (ft_putendl_fd("Error: Texture path is NULL", 2), false);
	if (ft_strlen(path) == 0)
		return (ft_putendl_fd("Error: Texture path is empty", 2), false);
	if (!check_texture_extension(path))
		return (false);
	trimmed_path = ft_strtrim(path, " \t\n\v\f\r");
	if (!trimmed_path)
		return (false);
	fd = open(trimmed_path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Cannot open texture file: ", 2);
		ft_putendl_fd((char *)path, 2);
		free(trimmed_path);
		return (false);
	}
	close(fd);
	free(trimmed_path);
	return (true);
}

bool	check_color_value(int r, int g, int b)
{
	if (r < 0 || r > 255)
	{
		ft_putendl_fd("Error: Red color value out of range (0-255)", 2);
		return (false);
	}
	if (g < 0 || g > 255)
	{
		ft_putendl_fd("Error: Green color value out of range (0-255)", 2);
		return (false);
	}
	if (b < 0 || b > 255)
	{
		ft_putendl_fd("Error: Blue color value out of range (0-255)", 2);
		return (false);
	}
	return (true);
}

bool	check_all_elements_set(t_asset *asset)
{
	if (!asset->no_path)
		return (ft_putendl_fd("Error: Missing North texture (NO)", 2), false);
	if (!asset->so_path)
		return (ft_putendl_fd("Error: Missing South texture (SO)", 2), false);
	if (!asset->we_path)
		return (ft_putendl_fd("Error: Missing West texture (WE)", 2), false);
	if (!asset->ea_path)
		return (ft_putendl_fd("Error: Missing East texture (EA)", 2), false);
	if (asset->floor.r < 0)
		return (ft_putendl_fd("Error: Missing floor color (F)", 2), false);
	if (asset->ceiling.r < 0)
		return (ft_putendl_fd("Error: Missing ceiling color (C)", 2), false);
	return (true);
}
