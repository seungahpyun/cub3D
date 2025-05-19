/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 11:33:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_texture_path(char *line, char **path)
{
	char	**split;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (!split[0] || !split[1] || split[2])
	{
		ft_free_strarr(split);
		return (-1);
	}
	*path = ft_strdup(split[1]);
	if (!(*path))
		ret = -1;
	else if (!check_texture_path(*path))
	{
		free(*path);
		*path = NULL;
		ret = -1;
	}
	ft_free_strarr(split);
	return (ret);
}

static bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (false);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	parse_color_value(char *line, t_color *color)
{
	char	**split;
	char	**rgb;
	int		ret;

	ret = 0;
	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	if (!split[0] || !split[1] || split[2])
		return (ft_free_strarr(split), -1);
	rgb = ft_split(split[1], ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_strarr(split);
		ft_free_strarr(rgb);
		ft_putendl_fd("Error: Invalid RGB format, use 'R,G,B'", 2);
		return (-1);
	}
	if (!is_numeric(rgb[0]) || !is_numeric(rgb[1]) || !is_numeric(rgb[2]))
	{
		ft_free_strarr(split);
		ft_free_strarr(rgb);
		ft_putendl_fd("Error: RGB values must be numeric", 2);
		return (-1);
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	ft_free_strarr(split);
	ft_free_strarr(rgb);
	if (!check_color_value(color->r, color->g, color->b))
		ret = -1;
	return (ret);
}

int	parse_element(char *line, t_asset *asset)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture_path(line, &asset->no_path));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture_path(line, &asset->so_path));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture_path(line, &asset->we_path));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_path(line, &asset->ea_path));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_value(line, &asset->floor));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_value(line, &asset->ceiling));
	return (-1);
}
