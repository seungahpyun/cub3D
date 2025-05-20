/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_processor.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 14:57:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 16:46:45 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '0'
			&& line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

int	process_line(char *line, t_game *game, int fd)
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

int	check_content_after_map(int fd)
{
	char	*line;
	int		ret;

	ret = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!is_empty_line(line))
		{
			ft_putendl_fd("Error: Content found after map section", 2);
			free(line);
			ret = -1;
			break;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (ret);
}

int	check_map_file(t_game *game, int fd, bool map_found)
{
	close(fd);
	if (!check_all_elements_set(&game->asset))
		return (free_game(game), -1);
	if (!map_found)
	{
		ft_putendl_fd("Error: No map found in file", 2);
		free_game(game);
		return (-1);
	}
	return (0);
}
