/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 08:55:27 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 11:54:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_line(char *line, t_game *game, int fd)
{
	int	ret;

	ret = 0;
	if (ft_strlen(line) <= 1 || line[0] == '\n')
	{
		free(line);
		return (0);
	}
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (parse_element(line, game) == -1)
	{
		if (parse_map(fd, game, line) == -1)
			ret = -1;
	}
	else
		free(line);
	return (ret);
}

int	parse_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	ret = 0;
	line = get_next_line(fd);
	while (line != NULL && ret == 0)
	{
		ret = process_line(line, game, fd);
		if (ret == 0)
			line = get_next_line(fd);
	}
	close(fd);
	return (ret);
}
