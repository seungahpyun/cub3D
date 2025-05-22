/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 09:04:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/05/22 11:32:59 by seungah       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "control.h"

void	move_player_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y - sin(game->player.angle) * MOVE_SPEED;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_player_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - cos(game->player.angle) * MOVE_SPEED;
	new_y = game->player.y + sin(game->player.angle) * MOVE_SPEED;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_player_left(t_game *game)
{
	double	new_x;
	double	new_y;
	double	left_angle;

	left_angle = game->player.angle + M_PI / 2;
	new_x = game->player.x + cos(left_angle) * MOVE_SPEED;
	new_y = game->player.y + sin(left_angle) * MOVE_SPEED;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	move_player_right(t_game *game)
{
	double	new_x;
	double	new_y;
	double	right_angle;

	right_angle = game->player.angle - M_PI / 2;
	new_x = game->player.x + cos(right_angle) * MOVE_SPEED;
	new_y = game->player.y + sin(right_angle) * MOVE_SPEED;
	if (can_move_to(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void	rotate_player_left(t_game *game)
{
	game->player.angle += ROTATE_SPEED;
	if (game->player.angle >= 2 * M_PI)
		game->player.angle -= 2 * M_PI;
}

void	rotate_player_right(t_game *game)
{
	game->player.angle -= ROTATE_SPEED;
	if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
}