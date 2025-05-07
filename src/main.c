/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/07 09:52:59 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/07 11:53:52 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_game(t_game *game)
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

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./cub3d <map.cub>", 2);
		return (EXIT_FAILURE);
	}
	if (!check_file_extension(argv[1]))
	{
		ft_putendl_fd("Error\nInvalid file extension. Use .cub", 2);
		return (EXIT_FAILURE);
	}
	init_game(&game);
	// if (parse_map(argv[1], &game) == -1)
	// {
	// 	free_game(&game);
	// 	return (EXIT_FAILURE);
	// }
}
