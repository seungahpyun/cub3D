/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 08:55:27 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 16:32:36 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	if (parse_element(line, &game->asset) == -1)
	{
		if (parse_map(fd, game, line) == -1)
			ret = -1;
	}
	else
		free(line);
	return (ret);
}

static int	check_content_after_map(int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			{
				free(line);
				ft_putendl_fd("Error: Content after map section", 2);
				return (-1);
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
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
	if (ret == 0 && check_content_after_map(fd) == -1)
		ret = -1;
	close(fd);
	if (ret == 0 && !check_all_elements_set(&game->asset))
		return (free_game(game), -1);
	return (ret);
}
