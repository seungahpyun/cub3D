/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   control.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/22 08:50:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 14:56:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_H
# define CONTROL_H

# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.1
# define ROTATE_LEFT 1
# define ROTATE_RIGHT -1

# include "common.h"

/* collision.c */
bool			can_move_to(t_game *game, double new_x, double new_y);
bool			can_move_x(t_game *game, double new_x);
bool			can_move_y(t_game *game, double new_y);
void			apply_sliding_movement(t_game *game,
					double new_x, double new_y);
/* keyboard_input.c */
void			handle_key_press(mlx_key_data_t keydata, void *param);
void			handle_window_close(void *param);
/* mouse_init.c */
void			handle_mouse_move(double xpos, double ypos, void *param);
/* player_movement.c */
void			move_player_forward(t_game *game);
void			move_player_backward(t_game *game);
void			move_player_left(t_game *game);
void			move_player_right(t_game *game);
void			rotate_player(t_game *game, int direction);

#endif
