/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   texture_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:07:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 16:29:53 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	validate_texture_format(const char *trimmed_path, const char *path)
{
	if (ft_strlen(trimmed_path) < 5)
		return (print_error_with_value("Texture file name is too short: ",
				path, false));
	if (!check_file_extension(trimmed_path, ".png"))
		return (print_error_with_value("Invalid texture file extension: ",
				path, false));
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
