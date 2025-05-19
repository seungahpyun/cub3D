/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_builder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/08 08:52:11 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 09:48:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_list	*create_map_node(char *line)
{
	char	*str_dup;
	t_list	*new_node;

	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	str_dup = ft_strdup(line);
	if (!str_dup)
		return (NULL);
	new_node = ft_lstnew(str_dup);
	if (!new_node)
	{
		free(str_dup);
		return (NULL);
	}
	return (new_node);
}

int	add_first_line(t_list **map_lines, char *first_line)
{
	t_list	*new_node;
	char	*str_dup;

	if (first_line && *first_line)
	{
		str_dup = ft_strdup(first_line);
		if (!str_dup)
		{
			free(first_line);
			return (-1);
		}
		new_node = ft_lstnew(str_dup);
		if (!new_node)
		{
			free(str_dup);
			free(first_line);
			return (-1);
		}
		ft_lstadd_back(map_lines, new_node);
	}
	free(first_line);
	return (0);
}

int	build_map_array(t_map *map, t_list *map_lines)
{
	t_list	*current;
	int		i;

	map->height = ft_lstsize(map_lines);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (-1);
	current = map_lines;
	i = 0;
	while (current)
	{
		map->grid[i++] = ft_strdup((char *)current->content);
		current = current->next;
	}
	map->grid[i] = NULL;
	map->width = get_map_width(map->grid);
	return (0);
}
