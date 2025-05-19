/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:52:59 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/19 17:40:24 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	setup_game(int argc, char **argv, t_game *game)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error: Usage: ./cub3d <map.cub>", 2);
		return (false);
	}
	if (!check_map_extension(argv[1]))
	{
		ft_putendl_fd("Error: Invalid file extension. Expected .cub", 2);
		return (false);
	}
	init_game_state(game);
	if (parse_file(argv[1], game) == -1)
	{
		ft_putendl_fd("Error: Failed to parse map", 2);
		free_game(game);
		return (false);
	}
	game->player_angle = dir_to_angle(game->player_dir);
	return (true);
}

static void	run_game(t_game *game)
{
	render_minimap(game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!setup_game(argc, argv, &game))
		return (EXIT_FAILURE);
	init_window(&game);
	run_game(&game);
	free_game(&game);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
