/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 08:52:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/12 10:52:25 by jianisong     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	handle_key_press(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W)
			move_player_forward(game);
		else if (keydata.key == MLX_KEY_S)
			move_player_backward(game);
		else if (keydata.key == MLX_KEY_A)
			move_player_left(game);
		else if (keydata.key == MLX_KEY_D)
			move_player_right(game);
		else if (keydata.key == MLX_KEY_LEFT)
			rotate_player(game, ROTATE_LEFT);
		else if (keydata.key == MLX_KEY_RIGHT)
			rotate_player(game, ROTATE_RIGHT);
		else if (keydata.key == MLX_KEY_SPACE)
			handle_door_interaction(&game->map, &game->player);
	}
}

void	handle_window_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	free_game(game);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}
