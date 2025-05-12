/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:20:25 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/12 15:32:32 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_file_extension(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL)
		return (false);
	if (ft_strcmp(dot, ".cub") != 0)
		return (false);
	return (true);
}

bool	check_texture_path(const char *path)
{
	int	fd;

	if (!path)
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

int	check_map_chars(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' ' &&
				map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E' &&
				map[i][j] != 'W')
				return (0);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' ||
				map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count == 1);
}
