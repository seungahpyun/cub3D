/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 16:10:39 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 16:10:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_file_extension(const char *path, const char *extension)
{
	const char	*dot;

	if (!path)
		return (false);
	dot = ft_strrchr(path, '.');
	if (!dot)
		return (false);
	return (ft_strcmp(dot, extension) == 0);
}
