/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/07 15:11:29 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_map_width(char **map)
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

static bool is_valid_map(char **map, t_game *game)
{
	int	i;
	int	j;

	if(!map || !game)
		return (false);
	if(!check_map_chars(map))
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
	return (true);
}

int	parse_map(int fd, t_game *game, char *first_line)
{
	t_list	*map_lines;
	t_list	*current;
	t_list	*new_node;
	char	*line;
	char	*str_dup;
	int		i;

	map_lines = NULL;
	if (first_line && *first_line)
	{
		str_dup = ft_strdup(first_line);
		if (!str_dup)
			return (-1);
		new_node = ft_lstnew(str_dup);
		if (!new_node)
		{
			free(str_dup);
			return (-1);
		}
		ft_lstadd_back(&map_lines, new_node);
	}
	free(first_line);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		str_dup = ft_strdup(line);
		if (!str_dup)
		{
			free(line);
			ft_lstclear(&map_lines, free);
			return (-1);
		}
		new_node = ft_lstnew(str_dup);
		if (!new_node)
		{
			free(str_dup);
			free(line);
			ft_lstclear(&map_lines, free);
			return (-1);
		}
		ft_lstadd_back(&map_lines, new_node);
		free(line);
	}
	close(fd);
	if (!map_lines)
	{
		ft_putendl_fd("Error: Empty map", 2);
		return (-1);
	}
	game->map_height = ft_lstsize(map_lines);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	if (!game->map)
	{
		ft_lstclear(&map_lines, free);
		return (-1);
	}
	current = map_lines;
	i = 0;
	while (current)
	{
		game->map[i++] = ft_strdup((char *)current->content);
		current = current->next;
	}
	game->map[i] = NULL;
	ft_lstclear(&map_lines, free);
	game->map_width = get_map_width(game->map);
	if (!is_valid_map(game->map, game))
	{
		free_map(game->map, game);
		return (-1);
	}
	printf("Parsed map:\n");
	for (i = 0; game->map[i]; i++)
	{
		printf("%s\n", game->map[i]);
	}
	return (0);
}
