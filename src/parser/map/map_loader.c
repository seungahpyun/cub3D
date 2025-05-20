/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_loader.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 10:16:08 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/20 16:22:52 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int	read_map_lines(int fd, t_list **map_lines, char *first_line)
{
	t_list	*new_node;
	char	*line;

	if (add_first_line(map_lines, first_line) == -1)
		return (-1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			break ;
		}
		if (!is_valid_map_line(line))
			return (free(line), ft_lstclear(map_lines, free), -1);
		new_node = create_map_node(line);
		if (!new_node)
			return (free(line), ft_lstclear(map_lines, free), -1);
		ft_lstadd_back(map_lines, new_node);
		free(line);
		line = get_next_line(fd);
	}
	if (!*map_lines)
		return (ft_putendl_fd("Error: Empty map", 2), -1);
	return (0);
}

bool	has_valid_first_line(char *line)
{
	int	i;
	int	valid_chars;
	int	total_chars;

	if (!line || is_empty_line(line))
		return (false);
	i = 0;
	valid_chars = 0;
	total_chars = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			total_chars++;
		if (is_map_char(line[i]))
		{
			if (line[i] == '0' || line[i] == '1'
				|| line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'E' || line[i] == 'W')
				valid_chars++;
		}
		else
			return (false);
		i++;
	}
	return (valid_chars > 0);
}
