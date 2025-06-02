/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:52:59 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/02 13:44:36 by spyun         ########   odam.nl         */
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
	return (true);
}

static void	run_game(t_game *game)
{
	init_input_system(game);
	setup_for_raycasting(game);
	if (!load_textures(game))
		ft_mlx_error(game);
	render(game);
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
