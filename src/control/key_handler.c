/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_handler.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 08:52:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/23 13:57:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	debug_player_position(t_game *game, char *action)
{
	printf("Action: %s\n", action);
	printf("Player Position: (%.2f, %.2f)\n", game->player.x, game->player.y);
	printf("Player Angle: %.2f (%.2f degrees)\n",
		game->player.angle, game->player.angle * 180 / M_PI);
	printf("Player Direction: %c\n", game->player.dir);
	printf("---\n");
}

// void	handle_key_press(mlx_key_data_t keydata, void *param)
// {
// 	t_game	*game;

// 	game = (t_game *)param;
// 	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
// 	{
// 		if (keydata.key == MLX_KEY_ESCAPE)
// 			mlx_close_window(game->mlx);
// 		else if (keydata.key == MLX_KEY_W)
// 			move_player_forward(game);
// 		else if (keydata.key == MLX_KEY_S)
// 			move_player_backward(game);
// 		else if (keydata.key == MLX_KEY_A)
// 			move_player_left(game);
// 		else if (keydata.key == MLX_KEY_D)
// 			move_player_right(game);
// 		else if (keydata.key == MLX_KEY_LEFT)
// 			rotate_player_left(game);
// 		else if (keydata.key == MLX_KEY_RIGHT)
// 			rotate_player_right(game);
// 	}
// }

void	handle_key_press(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		else if (keydata.key == MLX_KEY_W)
		{
			printf("Key pressed: W (Forward)\n");
			move_player_forward(game);
			debug_player_position(game, "Forward");
		}
		else if (keydata.key == MLX_KEY_S)
		{
			printf("Key pressed: S (Backward)\n");
			move_player_backward(game);
			debug_player_position(game, "Backward");
		}
		else if (keydata.key == MLX_KEY_A)
		{
			printf("Key pressed: A (Left)\n");
			move_player_left(game);
			debug_player_position(game, "Left");
		}
		else if (keydata.key == MLX_KEY_D)
		{
			printf("Key pressed: D (Right)\n");
			move_player_right(game);
			debug_player_position(game, "Right");
		}
		else if (keydata.key == MLX_KEY_LEFT)
		{
			printf("Key pressed: LEFT ARROW (Rotate Left)\n");
			rotate_player_left(game);
			debug_player_position(game, "Rotate Left");
		}
		else if (keydata.key == MLX_KEY_RIGHT)
		{
			printf("Key pressed: RIGHT ARROW (Rotate Right)\n");
			rotate_player_right(game);
			debug_player_position(game, "Rotate Right");
		}
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
