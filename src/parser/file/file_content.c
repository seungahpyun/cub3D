/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_content.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 14:58:06 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 16:46:16 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_map_content(t_game *game, int fd, int ret)
{
	bool	map_found;
	char	*line;

	map_found = false;
	line = get_next_line(fd);
	while (line != NULL && ret == 0)
	{
		ret = process_line(line, game, fd);
		if (ret == 1)
		{
			map_found = true;
			if (check_content_after_map(fd) == -1)
			{
				ret = -1;
				break ;
			}
		}
		if (ret == 0)
			line = get_next_line(fd);
	}
	if (ret == 0)
		ret = check_map_file(game, fd, map_found);
	return (ret);
}
