/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:52:59 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/13 11:57:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game_state(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
	game->map = NULL;
	game->player_x = -1;
	game->player_y = -1;
	game->player_dir = '\0';
}

static bool	setup_game(int argc, char **argv, t_game *game)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error: Usage: ./cub3d <map.cub>", 2);
		return (false);
	}
	if (!check_map_extension(argv[1]))
	{
		ft_putendl_fd("Error: nInvalid file extension. Expected .cub", 2);
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

static void	init_window(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!game->mlx)
		ft_mlx_error(game);
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
