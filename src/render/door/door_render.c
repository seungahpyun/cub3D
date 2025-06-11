/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   door_render.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/06 15:03:34 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/11 23:14:04 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	draw_textured_door(t_game *game, t_render_data *render_data)
{
	int			i;
	int			cx;
	int			cy;
	t_door		*door;
	mlx_image_t	*door_tex;

	if (!game || !render_data)
		return ;
	i = render_data->x;
	cx = game->rays[i].map_x;
	cy = game->rays[i].map_y;
	door = &game->map.doors[cy][cx];
	if (!game->asset.door_img)
		return ;
	door_tex = game->asset.door_img;
}
