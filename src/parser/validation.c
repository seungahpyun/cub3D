/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:20:25 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/07 10:31:08 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_extension(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot == NULL)
		return (0);
	if (ft_strcmp(dot, ".cub") != 0)
		return (0);
	return (1);
}
