/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:07:53 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 15:32:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_handle_char(char *trimmed, int *i, int *j, int *in_space)
{
	if (ft_isspace(trimmed[*i]))
	{
		if (!(*in_space))
		{
			trimmed[(*j)++] = ' ';
			*in_space = 1;
		}
	}
	else
	{
		trimmed[(*j)++] = trimmed[*i];
		*in_space = 0;
	}
	(*i)++;
}

char	*ft_trim_and_compact(char *str)
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
		ft_handle_char(trimmed, &i, &j, &in_space);
	trimmed[j] = '\0';
	return (trimmed);
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
