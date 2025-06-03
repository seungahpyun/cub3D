/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_memory.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 11:34:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/03 16:42:33 by jsong         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "render.h"

static void	free_door_states(int **door_states, int height)
{
	int	i;

	if (!door_states)
		return ;
	i = 0;
	while (i < height)
	{
		if (door_states[i])
			free(door_states[i]);
		i++;
	}
	free(door_states);
	door_states = NULL;
}

static void	free_door_openness(double **door_openness, int height)
{
	int	i;

	if (!door_openness)
		return ;
	i = 0;
	while (i < height)
	{
		if (door_openness[i])
			free(door_openness[i]);
		i++;
	}
	free(door_openness);
	door_openness = NULL;
}

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
	free_door_states(map->door_states, map->height);
	free_door_openness(map->door_openness, map->height);
}

static void	free_asset_paths(t_asset *asset)
{
	if (!asset)
		return ;
	if (asset->no_path)
		free(asset->no_path);
	if (asset->so_path)
		free(asset->so_path);
	if (asset->we_path)
		free(asset->we_path);
	if (asset->ea_path)
		free(asset->ea_path);
	if (asset->door_path)
		free(asset->door_path);
	asset->no_path = NULL;
	asset->so_path = NULL;
	asset->we_path = NULL;
	asset->ea_path = NULL;
	asset->door_path = NULL;
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
	free_asset_paths(&game->asset);
	if (game->mlx)
		free_textures(game);
	if (game->mlx && game->minimap.img)
	{
		mlx_delete_image(game->mlx, game->minimap.img);
		game->minimap.img = NULL;
	}
}
