/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:07:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/04 17:52:05 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_texture_extension(const char *path)
{
	const char	*dot;

	if (!path)
		return (false);
	dot = ft_strrchr(path, '.');
	if (!dot)
		return (false);
	return (ft_strcmp(dot, ".png") == 0);
}

static int	validate_texture(char **path, char **split)
{
	int	ret;

	ret = 0;
	*path = ft_strdup(split[1]);
	if (!(*path))
		ret = -1;
	else if (!check_texture_path(*path))
	{
		ft_putendl_fd("Error: Invalid texture path", 2);
		free(*path);
		*path = NULL;
		ret = -1;
	}
	ft_free_strarr(split);
	return (ret);
}

int	parse_texture_path(char *line, char **path)
{
	char	*trimmed;
	char	**split;

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
	return (validate_texture(path, split));
}
