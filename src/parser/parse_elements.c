/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 12:04:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_trim_and_compact(char *str)
{
	char	*trimmed;
	int		i;
	int		j;
	int		in_space;

	trimmed = ft_strtrim(str, " \t\n\v\f\r");
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	in_space = 0;
	while (trimmed[i])
	{
		if (ft_isspace(trimmed[i]))
		{
			if (!in_space)
			{
				trimmed[j++] = ' ';
				in_space = 1;
			}
		}
		else
		{
			trimmed[j++] = trimmed[i];
			in_space = 0;
		}
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

static int	parse_texture_path(char *line, char **path)
{
	char	*trimmed;
	char	**split;
	int		ret;

	ret = 0;
	if (*path != NULL)
		return (ft_putendl_fd("Error: Duplicate texture path", 2), -1);
	trimmed = ft_trim_and_compact(line);
	if (!trimmed)
		return (-1);
	split = ft_split(trimmed, ' ');
	free(trimmed);
	if (!split)
		return (-1);
	if (!split[0] || !split[1] || split[2])
		return (ft_free_strarr(split), -1);
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

static int	extract_rgb_values(char *line, t_color *color)
{
	int		i;
	int		j;
	int		values[3];
	char	*str;
	bool	negative;

	if (color->r >= 0)
	{
		ft_putendl_fd("Error: Duplicate color value", 2);
		return (-1);
	}
	str = line;
	while (*str && *str != ' ')
		str++;
	while (*str && *str == ' ')
		str++;
	i = 0;
	while (i < 3)
	{
		while (*str && (*str == ' ' || *str == ','))
			str++;
		negative = false;
		if (*str == '-')
		{
			negative = true;
			str++;
		}
		else if (*str == '+')
		{
			str++;
		}
		j = 0;
		values[i] = 0;
		while (*str && ft_isdigit(*str))
		{
			values[i] = values[i] * 10 + (*str - '0');
			str++;
			j++;
		}
		if (negative)
			values[i] = -values[i];
		if (j == 0)
			return (-1);
		i++;
	}
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	if (!check_color_value(color->r, color->g, color->b))
	{
		color->r = -1;
		color->g = -1;
		color->b = -1;
		return (-1);
	}
	return (0);
}

static int	parse_color_value(char *line, t_color *color)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_trim_and_compact(line);
	if (!trimmed)
		return (-1);
	ret = extract_rgb_values(trimmed, color);
	free(trimmed);
	return (ret);
}

int	parse_element(char *line, t_asset *asset)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_trim_and_compact(line);
	if (!trimmed)
		return (-1);
	ret = -1;
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		ret = parse_texture_path(line, &asset->no_path);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		ret = parse_texture_path(line, &asset->so_path);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		ret = parse_texture_path(line, &asset->we_path);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		ret = parse_texture_path(line, &asset->ea_path);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		ret = parse_color_value(line, &asset->floor);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		ret = parse_color_value(line, &asset->ceiling);
	free(trimmed);
	return (ret);
}
