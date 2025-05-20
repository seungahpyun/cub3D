/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 11:54:47 by spyun         ########   odam.nl         */
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

static bool	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == '\t' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static bool	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_map_char(line[i]) && line[i] != '\n')
		{
			ft_putstr_fd("Error: Invalid character in map: '", 2);
			ft_putchar_fd(line[i], 2);
			ft_putendl_fd("'", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static int	read_map_lines(int fd, t_list **map_lines, char *first_line)
{
	t_list	*new_node;
	char	*line;

	printf("DEBUG [read_map_lines]: Adding first line: '%s'\n", first_line);
	if (add_first_line(map_lines, first_line) == -1)
	{
		printf("DEBUG [read_map_lines]: Failed to add first line\n");
		return (-1);
	}

	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("DEBUG [read_map_lines]: Reading line: '%s'\n", line);
		if (is_empty_line(line))
		{
			printf("DEBUG [read_map_lines]: Empty line found, stopping map parsing\n");
			free(line);
			break;
		}
		if (!is_valid_map_line(line))
		{
			printf("DEBUG [read_map_lines]: Invalid map line found\n");
			free(line);
			ft_lstclear(map_lines, free);
			return (-1);
		}
		new_node = create_map_node(line);
		if (!new_node)
		{
			printf("DEBUG [read_map_lines]: Failed to create map node\n");
			return (free(line), ft_lstclear(map_lines, free), -1);
		}

		ft_lstadd_back(map_lines, new_node);
		free(line);
		line = get_next_line(fd);
	}

	if (!*map_lines)
	{
		printf("DEBUG [read_map_lines]: Map is empty\n");
		return (ft_putendl_fd("Error: Empty map", 2), -1);
	}

	return (0);
}

static bool	has_valid_first_line(char *line)
{
	int	i;
	int	valid_chars;
	int	total_chars;

	printf("DEBUG [has_valid_first_line]: Checking line: '%s'\n", line);
	if (!line || is_empty_line(line))
	{
		printf("DEBUG [has_valid_first_line]: Line is NULL or empty\n");
		return (false);
	}
	i = 0;
	valid_chars = 0;
	total_chars = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			total_chars++;
		if (is_map_char(line[i]))
		{
			if (line[i] == '0' || line[i] == '1' ||
				line[i] == 'N' || line[i] == 'S' ||
				line[i] == 'E' || line[i] == 'W')
				valid_chars++;
		}
		else
		{
			printf("DEBUG [has_valid_first_line]: Invalid character: '%c'\n", line[i]);
			return (false);
		}
		i++;
	}
	printf("DEBUG [has_valid_first_line]: Valid chars count: %d, Total non-space: %d\n",
		valid_chars, total_chars);
	return (valid_chars > 0);
}

int	parse_map(int fd, t_game *game, char *first_line)
{
	t_list	*map_lines;

	printf("DEBUG [parse_map]: Parsing map with first line: '%s'\n", first_line);
	if (!has_valid_first_line(first_line))
	{
		printf("DEBUG [parse_map]: First line is not valid\n");
		free(first_line);
		return (-1);
	}
	if (!check_all_elements_set(&game->asset))
	{
		printf("DEBUG [parse_map]: Not all elements are set\n");
		return (free(first_line), -1);
	}
	map_lines = NULL;
	if (read_map_lines(fd, &map_lines, first_line) == -1)
	{
		printf("DEBUG [parse_map]: Failed to read map lines\n");
		return (-1);
	}
	if (build_map_array(&game->map, map_lines) == -1)
	{
		printf("DEBUG [parse_map]: Failed to build map array\n");
		ft_lstclear(&map_lines, free);
		return (-1);
	}
	ft_lstclear(&map_lines, free);
	if (!validate_map(&game->map, &game->player))
	{
		printf("DEBUG [parse_map]: Map validation failed\n");
		free_map(&game->map);
		return (-1);
	}
	printf("DEBUG [parse_map]: Map parsing successful\n");
	return (1);
}
