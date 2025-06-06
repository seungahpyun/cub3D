/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 14:23:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 14:27:11 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

uint32_t	get_pixel_color(mlx_image_t *texture, int tex_x, int tex_y)
{
	int			pixel_index;
	uint8_t		*pixel_ptr;
	uint32_t	color;

	if (!texture || !texture->pixels)
		return (DEFAULT_TEXTURE_COLOR);
	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (DEFAULT_TEXTURE_COLOR);
	pixel_index = (tex_y * texture->width + tex_x) * 4;
	pixel_ptr = texture->pixels + pixel_index;
	color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
		| (pixel_ptr[2] << 8) | pixel_ptr[3];
	return (color);
}
