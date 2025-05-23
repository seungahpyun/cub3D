/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 09:04:17 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/23 13:57:22 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

// bool	can_move_to(t_game *game, double new_x, double new_y)
// {
// 	int	map_x;
// 	int	map_y;

// 	map_x = (int)new_x;
// 	map_y = (int)new_y;
// 	if (map_y < 0 || map_y >= game->map.height)
// 		return (false);
// 	if (map_x < 0 || map_x >= (int)ft_strlen(game->map.grid[map_y]))
// 		return (false);
// 	if (game->map.grid[map_y][map_x] == '1')
// 		return (false);
// 	if (game->map.grid[map_y][map_x] == ' ')
// 		return (false);
// 	return (true);
// }

static void	debug_collision_check(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	printf("Collision Check:\n");
	printf("  New position: (%.2f, %.2f) -> Map cell: (%d, %d)\n",
		new_x, new_y, map_x, map_y);
	printf("  Map bounds: height=%d, width=%d\n",
		game->map.height, game->map.width);
	if (map_y >= 0 && map_y < game->map.height &&
		map_x >= 0 && map_x < (int)ft_strlen(game->map.grid[map_y]))
		printf("  Cell content: '%c'\n", game->map.grid[map_y][map_x]);
	else
		printf("  Cell content: OUT OF BOUNDS\n");
}

bool	can_move_to(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	debug_collision_check(game, new_x, new_y);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_y < 0 || map_y >= game->map.height)
	{
		printf("  Result: OUT OF BOUNDS (Y)\n");
		return (false);
	}
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map.grid[map_y]))
	{
		printf("  Result: OUT OF BOUNDS (X)\n");
		return (false);
	}
	if (game->map.grid[map_y][map_x] == '1')
	{
		printf("  Result: WALL\n");
		return (false);
	}
	if (game->map.grid[map_y][map_x] == ' ')
	{
		printf("  Result: SPACE\n");
		return (false);
	}
	printf("  Result: CAN MOVE\n");
	return (true);
}
