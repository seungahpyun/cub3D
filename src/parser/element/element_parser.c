/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:07:53 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/03 15:43:44 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	else if (ft_strncmp(trimmed, "DOOR ", 5) == 0)
		ret = parse_texture_path(line, &asset->door_path);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		ret = parse_color_value(line, &asset->floor);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		ret = parse_color_value(line, &asset->ceiling);
	free(trimmed);
	return (ret);
}
