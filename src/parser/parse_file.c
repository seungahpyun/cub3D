/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 08:55:27 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 12:06:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0' &&
			line[i] != '1' && line[i] != 'N' && line[i] != 'S' &&
			line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

static int	process_line(char *line, t_game *game, int fd)
{
	int	ret;

	ret = 0;
	if (is_empty_line(line))
		return (free(line), 0);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (is_map_line(line) && check_all_elements_set(&game->asset))
		ret = parse_map(fd, game, line);
	else
	{
		ret = parse_element(line, &game->asset);
		if (ret == -1)
		{
			free(line);
			ret = -1;
		}
		else
			free(line);
	}
	return (ret);
}

static int	check_content_after_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_empty_line(line))
		{
			ft_putendl_fd("Error: Content found after map section", 2);
			free(line);
			while ((line = get_next_line(fd)) != NULL)
				free(line);
			return (-1);
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
	bool	map_found;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	ret = 0;
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
				break;
			}
		}
		if (ret == 0)
			line = get_next_line(fd);
	}
	close(fd);
	if (ret == 0 && !check_all_elements_set(&game->asset))
	{
		free_game(game);
		return (-1);
	}
	if (ret == 0 && !map_found)
	{
		ft_putendl_fd("Error: No map found in file", 2);
		free_game(game);
		return (-1);
	}
	return (ret);
}
