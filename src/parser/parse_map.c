/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 10:36:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_map_width(char **map)
{
	int	i;
	int	max_width;
	int	len;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

static bool	is_valid_map(char **map, t_game *game)
{
	int	i;
	int	j;

	if (!map || !game)
		return (false);
	if (!check_map_chars(map))
		return (ft_putendl_fd("Error: Invalid characters in map", 2), false);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				game->player_x = j;
				game->player_y = i;
				game->player_dir = map[i][j];
			}
			j++;
		}
		i++;
	}
	if (!validate_map_closure(game))
		return (false);
	return (true);
}

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
	if (build_map_array(game, map_lines) == -1)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}
	ft_lstclear(&map_lines, free);
	if (!is_valid_map(game->map, game))
	{
		free_map(game->map, game);
		return (-1);
	}
	return (0);
}
