/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/05/09 17:48:06 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_minimap(t_game *game)
{
	game->minimap = mlx_new_image(game->mlx, 512, 512);
	if (!game->minimap)
		ft_mlx_error(game);
	// Set every pixel to white
	ft_memset(game->minimap->pixels, 255, game->minimap->width
		* game->minimap->height * sizeof(int32_t));
	if (mlx_image_to_window(game->mlx, game->minimap, 0, 0) < 0)
		ft_mlx_error(game);
}
