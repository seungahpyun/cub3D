/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_init.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 08:51:40 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/22 11:03:24 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	handle_mouse_move(double xpos, double ypos, void *param)
{
	t_game		*game;
	static int	last_x = -1;
	int			delta_x;

	game = (t_game *)param;
	if (last_x == -1)
		last_x = (int)xpos;
	delta_x = (int)xpos - last_x;
	if (delta_x != 0)
	{
		game->player.angle -= delta_x * 0.001;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
		else if (game->player.angle >= 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	last_x = (int)xpos;
	(void)ypos;
}

void	init_input_system(t_game *game)
{
	mlx_key_hook(game->mlx, &handle_key_press, game);
	mlx_cursor_hook(game->mlx, &handle_mouse_move, game);
	mlx_close_hook(game->mlx, &handle_window_close, game);
}