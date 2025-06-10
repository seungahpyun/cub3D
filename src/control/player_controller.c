/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_controller.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 09:04:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 14:36:24 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	move_player_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED;
	if (!can_move_to(game, new_x, new_y))
	{
		new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED / 4;
		new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED / 4;
	}
	apply_sliding_movement(game, new_x, new_y);
}

void	move_player_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
	if (!can_move_to(game, new_x, new_y))
	{
		new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED / 4;
		new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED / 4;
	}
	apply_sliding_movement(game, new_x, new_y);
}

void	move_player_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - sin(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y - cos(game->player.angle) * MOVE_SPEED;
	if (!can_move_to(game, new_x, new_y))
	{
		new_x = game->player.x - sin(game->player.angle) * MOVE_SPEED / 4;
		new_y = game->player.y - cos(game->player.angle) * MOVE_SPEED / 4;
	}
	apply_sliding_movement(game, new_x, new_y);
}

void	move_player_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + sin(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y + cos(game->player.angle) * MOVE_SPEED;
	if (!can_move_to(game, new_x, new_y))
	{
		new_x = game->player.x + sin(game->player.angle) * MOVE_SPEED / 4;
		new_y = game->player.y + cos(game->player.angle) * MOVE_SPEED / 4;
	}
	apply_sliding_movement(game, new_x, new_y);
}

void	rotate_player(t_game *game, int direction)
{
	if (direction == ROTATE_LEFT)
		game->player.angle += ROTATE_SPEED;
	else if (direction == ROTATE_RIGHT)
		game->player.angle -= ROTATE_SPEED;
	game->player.angle = normalize_angle(game->player.angle);
}
