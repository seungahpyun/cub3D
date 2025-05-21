/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/20 15:07:58 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/21 15:08:50 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_rgb_values(char *str, int values[3])
{
	int	i;
	int	j;
	int	comma_count;

	comma_count = count_color_commas(str);
	if (comma_count < 2)
		return (ft_putendl_fd("Error: Missing comma in color values", 2), -1);
	if (comma_count > 2)
		return (ft_putendl_fd("Error: Too many commas in color values", 2), -1);
	i = 0;
	while (i < 3)
	{
		j = parse_color_component(&str, &values[i]);
		if (j == 0)
			return (ft_putendl_fd("Error: Invalid color component", 2), -1);
		i++;
	}
	if (check_extra_color_chars(str) == -1)
		return (ft_putendl_fd("Error: Extra characters after color", 2), -1);
	return (0);
}

static int	set_color_values(t_color *color, int values[3])
{
	color->r = values[0];
	color->g = values[1];
	color->b = values[2];
	if (!check_color_value(color->r, color->g, color->b))
	{
		color->r = -1;
		color->g = -1;
		color->b = -1;
		return (-1);
	}
	return (0);
}

static int	extract_rgb_values(char *line, t_color *color)
{
	int		values[3];
	char	*str;

	if (color->r >= 0)
		return (ft_putendl_fd("Error: Duplicate color value", 2), -1);
	str = line;
	while (*str && *str != ' ')
		str++;
	while (*str && *str == ' ')
		str++;
	if (parse_rgb_values(str, values) == -1)
		return (-1);
	return (set_color_values(color, values));
}

int	parse_color_value(char *line, t_color *color)
{
	char	*trimmed;
	int		ret;

	trimmed = ft_trim_and_compact(line);
	if (!trimmed)
		return (-1);
	ret = extract_rgb_values(trimmed, color);
	free(trimmed);
	return (ret);
}
