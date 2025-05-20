/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:07:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 15:33:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	print_texture_error(const char *error_msg, const char *path)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd((char *)error_msg, 2);
	ft_putendl_fd((char *)path, 2);
	return (false);
}

static bool	validate_texture_format(const char *trimmed_path, const char *path)
{
	const char	*dot;

	if (ft_strlen(trimmed_path) < 5)
		return (print_texture_error("Texture file name is too short: ", path));
	dot = ft_strrchr(trimmed_path, '.');
	if (!dot)
		return (print_texture_error("Texture file has no extension: ", path));
	else if (ft_strcmp(dot, ".png") != 0)
		return (print_texture_error("Invalid texture file extension: ", path));
	return (true);
}

bool	check_texture_extension(const char *path)
{
	char		*trimmed_path;
	bool		ret;

	trimmed_path = ft_strtrim(path, " \t\n\v\f\r");
	if (!trimmed_path)
		return (false);
	ret = validate_texture_format(trimmed_path, path);
	free(trimmed_path);
	return (ret);
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
