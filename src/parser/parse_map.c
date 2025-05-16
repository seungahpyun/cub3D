/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/16 11:10:59 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_map_lines(int fd, t_list **map_lines, char *first_line)
{
	t_list	*new_node;
	char	*line;

	if (add_first_line(map_lines, first_line) == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		new_node = create_map_node(line);
		if (!new_node)
		{
			free(line);
			ft_lstclear(map_lines, free);
			return (-1);
		}
		ft_lstadd_back(map_lines, new_node);
		free(line);
		line = get_next_line(fd);
	}
	if (!*map_lines)
		return (ft_putendl_fd("Error: Empty map", 2), -1);
	return (0);
}

int	parse_map(int fd, t_game *game, char *first_line)
{
	t_list	*map_lines;

	map_lines = NULL;
	if (read_map_lines(fd, &map_lines, first_line) == -1)
		return (-1);
	if (build_map_array(&game->map, map_lines) == -1)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}
	ft_lstclear(&map_lines, free);
	if (!validate_map(&game->map, &game->player))
	{
		free_map(&game->map);
		return (-1);
	}
	return (0);
}
