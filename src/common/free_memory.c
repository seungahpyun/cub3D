/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 11:34:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:58:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "render.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx)
	{
		free_textures(game);
		free_all_sprites(game);
	}
	free_map(&game->map);
	free_asset(&game->asset, game->mlx);
	if (game->mlx && game->minimap.img)
	{
		mlx_delete_image(game->mlx, game->minimap.img);
		game->minimap.img = NULL;
	}
}
