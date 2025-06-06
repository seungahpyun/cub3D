/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/06 19:05:00 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	color_to_rgba(t_color *color, int a)
{
	return (color->r << 24 | color->g << 16 | color->b << 8 | a);
}

double	degree_to_radian(double degree)
{
	if (degree < 0)
		degree += 360;
	return (degree * M_PI / 180);
}

int	is_coordinate_valid(int x, int y, int width, int height)
{
	return (x >= 0 && y >= 0 && x < width && y < height);
}

bool	is_valid_point(t_map *map, int mx, int my)
{
	if (!is_coordinate_valid(mx, my, map->width, map->height))
		return (false);
	if (mx >= (int)ft_strlen(map->grid[my]))
		return (false);
	return (true);
}

int	get_color(char c)
{
	if (c == '1')
		return (MINIMAP_WALL_COLOR);
	if (c == ' ')
		return (MINIMAP_EMPTY_COLOR);
	return (MINIMAP_FLOOR_COLOR);
}
