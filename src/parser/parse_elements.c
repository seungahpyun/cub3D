/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_elements.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 10:45:33 by spyun         ########   odam.nl         */
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
	{
		ft_putendl_fd("Error: Duplicate texture path", 2);
		return (-1);
	}
	trimmed = ft_trim_and_compact(line);
	if (!trimmed)
		return (-1);
	printf("DEBUG [parse_texture_path]: Trimmed line: '%s'\n", trimmed);
	split = ft_split(trimmed, ' ');
	free(trimmed);
	if (!split)
		return (-1);
	if (!split[0] || !split[1] || split[2])
	{
		printf("DEBUG [parse_texture_path]: Invalid format\n");
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
	else
		printf("DEBUG [parse_texture_path]: Successfully parsed path: '%s'\n", *path);
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
	printf("DEBUG: Raw RGB values: %d, %d, %d\n", color->r, color->g, color->b);
	if (!check_color_value(color->r, color->g, color->b))
	{
		printf("DEBUG: RGB values out of range\n");
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

	printf("DEBUG [parse_color_value]: Trimmed line: '%s'\n", trimmed);
	ret = extract_rgb_values(trimmed, color);

	if (ret == 0)
		printf("DEBUG [parse_color_value]: Successfully parsed color: (%d, %d, %d)\n",
			color->r, color->g, color->b);
	else
		printf("DEBUG [parse_color_value]: Failed to parse color\n");

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

	printf("DEBUG [parse_element]: Original line: '%s'\n", line);
	printf("DEBUG [parse_element]: Trimmed line: '%s'\n", trimmed);

	ret = -1;
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		printf("DEBUG [parse_element]: Found NO element\n");
		ret = parse_texture_path(line, &asset->no_path);
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		printf("DEBUG [parse_element]: Found SO element\n");
		ret = parse_texture_path(line, &asset->so_path);
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		printf("DEBUG [parse_element]: Found WE element\n");
		ret = parse_texture_path(line, &asset->we_path);
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		printf("DEBUG [parse_element]: Found EA element\n");
		ret = parse_texture_path(line, &asset->ea_path);
	}
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		printf("DEBUG [parse_element]: Found F element\n");
		ret = parse_color_value(line, &asset->floor);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		printf("DEBUG [parse_element]: Found C element\n");
		ret = parse_color_value(line, &asset->ceiling);
	}
	else
		printf("DEBUG [parse_element]: Element not recognized\n");

	free(trimmed);
	return (ret);
}
