/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file_parser.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 08:55:27 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/06 19:38:02 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parse_file(char *filename, t_game *game)
{
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), -1);
	ret = 0;
	ret = parse_map_content(game, fd, ret);
	gnl_cleanup(fd);
	close(fd);
	return (ret);
}

int	parse_map(int fd, t_game *game, char *first_line)
{
	t_list	*map_lines;

	if (!has_valid_first_line(first_line))
		return (free(first_line), -1);
	map_lines = NULL;
	if (read_map_lines(fd, &map_lines, first_line) == -1)
		return (-1);
	if (build_map_array(&game->map, map_lines) == -1)
		return (ft_lstclear(&map_lines, free), -1);
	ft_lstclear(&map_lines, free);
	if (!validate_map(&game->map, &game->player, &game->asset.animated_sprite))
		return (free_map(&game->map), -1);
	return (1);
}
