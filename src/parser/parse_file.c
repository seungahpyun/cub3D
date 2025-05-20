/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_file.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 08:55:27 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 11:54:39 by spyun         ########   odam.nl         */
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

	printf("DEBUG [process_line]: Processing line: '%s'\n", line);
	ret = 0;
	if (is_empty_line(line))
	{
		printf("DEBUG [process_line]: Empty line, skipping\n");
		free(line);
		return (0);
	}
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	if (is_map_line(line) && check_all_elements_set(&game->asset))
	{
		printf("DEBUG [process_line]: Line appears to be a map line\n");
		ret = parse_map(fd, game, line);
		if (ret == -1)
			printf("DEBUG [process_line]: Failed to parse as map\n");
		else
			printf("DEBUG [process_line]: Parsed as map successfully\n");
	}
	else
	{
		ret = parse_element(line, &game->asset);
		if (ret == -1)
		{
			printf("DEBUG [process_line]: Not a recognized element or map line\n");
			free(line);
			ret = -1;
		}
		else
		{
			printf("DEBUG [process_line]: Parsed as element successfully\n");
			free(line);
		}
	}
	return (ret);
}

static int	check_content_after_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("DEBUG [check_content_after_map]: Checking line: '%s'\n", line);
		if (!is_empty_line(line))
		{
			printf("DEBUG [check_content_after_map]: Found non-empty line after map: '%s'\n", line);
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

	printf("DEBUG [parse_file]: Parsing file: %s\n", filename);
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
	printf("DEBUG [parse_file]: All elements set check\n");
	printf("DEBUG [parse_file]: NO path: %s\n", game->asset.no_path ? game->asset.no_path : "NULL");
	printf("DEBUG [parse_file]: SO path: %s\n", game->asset.so_path ? game->asset.so_path : "NULL");
	printf("DEBUG [parse_file]: WE path: %s\n", game->asset.we_path ? game->asset.we_path : "NULL");
	printf("DEBUG [parse_file]: EA path: %s\n", game->asset.ea_path ? game->asset.ea_path : "NULL");
	printf("DEBUG [parse_file]: Floor color: (%d, %d, %d)\n", game->asset.floor.r, game->asset.floor.g, game->asset.floor.b);
	printf("DEBUG [parse_file]: Ceiling color: (%d, %d, %d)\n", game->asset.ceiling.r, game->asset.ceiling.g, game->asset.ceiling.b);
	if (ret == 0 && !check_all_elements_set(&game->asset))
	{
		printf("DEBUG [parse_file]: Not all elements are set\n");
		free_game(game);
		return (-1);
	}
	if (ret == 0 && !map_found)
	{
		printf("DEBUG [parse_file]: No map found in file\n");
		ft_putendl_fd("Error: No map found in file", 2);
		free_game(game);
		return (-1);
	}
	printf("DEBUG [parse_file]: Parsing complete with result: %d\n", ret);
	return (ret);
}
