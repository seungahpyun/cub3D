/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 11:34:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 14:15:49 by spyun         ########   odam.nl         */
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
	while (i < map->height && map->grid[i])
	{
		free(map->grid[i]);
		map->grid[i] = NULL;
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
		free_all_sprites(game);
		if (game->minimap.img)
		{
			mlx_delete_image(game->mlx, game->minimap.img);
			game->minimap.img = NULL;
		}
	}
	free_map(&game->map);
	free_asset(&game->asset, game->mlx);
}
