/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minimap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsong <jsong@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/09 15:21:43 by jsong         #+#    #+#                 */
/*   Updated: 2025/06/17 11:26:54 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	calculate_offset(t_player *player, t_minimap *minimap)
{
	int	w_px;
	int	w_py;
	int	s_px;
	int	s_py;

	w_px = (int)(player->x * MINIMAP_CELL_SIZE);
	w_py = (int)(player->y * MINIMAP_CELL_SIZE);
	s_px = MINIMAP_W / 2;
	s_py = MINIMAP_H / 2;
	minimap->offset_x = w_px - s_px;
	minimap->offset_y = w_py - s_py;
}

void	render_minimap(t_game *game)
{
	calculate_offset(&game->player, &game->minimap);
	draw_minimap_grid(&game->map, &game->minimap);
	draw_minimap_rays(game->rays, &game->minimap);
	draw_minimap_doors(&game->map, &game->minimap);
	draw_minimap_sprites(&game->map, &game->minimap);
	draw_minimap_player(&game->player, &game->minimap);
}
