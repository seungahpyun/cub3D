/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 11:08:44 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/10 14:42:54 by spyun         ########   odam.nl         */
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

int	get_color(char c)
{
	if (c == '1')
		return (MINIMAP_WALL_COLOR);
	if (c == ' ')
		return (MINIMAP_EMPTY_COLOR);
	return (MINIMAP_FLOOR_COLOR);
}
