/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 11:34:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/10 15:22:48 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "render.h"

static void	free_2d_array(void **arr, int rows)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (i < rows)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map(t_map *map)
{
	int	rows;

	if (!map)
		return ;
	rows = map->height;
	if (rows <= 0)
		return ;
	free_2d_array((void **)map->grid, rows);
	map->grid = NULL;
	free_2d_array((void **)map->doors, rows);
	map->doors = NULL;
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
