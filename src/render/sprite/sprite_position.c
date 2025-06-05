/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_position.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/05 11:50:33 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:52:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static void	calculate_sprite_distance_and_angle(t_game *game, t_sprite *sprite,
									double *distance, double *angle_diff)
{
	double	dx;
	double	dy;
	double	sprite_angle;

	dx = sprite->x - game->player.x;
	dy = sprite->y - game->player.y;
	*distance = sqrt(dx * dx + dy * dy);
	if (*distance <= 0.1)
		return ;
	sprite_angle = atan2(-dy, dx);
	*angle_diff = sprite_angle - game->player.angle;
	while (*angle_diff > M_PI)
		*angle_diff -= 2 * M_PI;
	while (*angle_diff < -M_PI)
		*angle_diff += 2 * M_PI;
}

static void	calculate_sprite_dimensions(double distance, double angle_diff,
									t_sprite_render *render)
{
	render->screen_x = (WIDTH / 2) - (angle_diff / (FOV * M_PI / 180)) * WIDTH;
	render->sprite_height = (int)(HEIGHT / distance);
	render->sprite_width = render->sprite_height;
	render->draw_start_y = -render->sprite_height / 2 + HEIGHT / 2;
	if (render->draw_start_y < 0)
		render->draw_start_y = 0;
	render->draw_end_y = render->sprite_height / 2 + HEIGHT / 2;
	if (render->draw_end_y >= HEIGHT)
		render->draw_end_y = HEIGHT - 1;
	render->draw_start_x = -render->sprite_width / 2 + (int)render->screen_x;
	if (render->draw_start_x < 0)
		render->draw_start_x = 0;
	render->draw_end_x = render->sprite_width / 2 + (int)render->screen_x;
	if (render->draw_end_x >= WIDTH)
		render->draw_end_x = WIDTH - 1;
}

void	calculate_sprite_screen_pos(t_game *game, t_sprite *sprite,
									t_sprite_render *render)
{
	double	distance;
	double	angle_diff;

	calculate_sprite_distance_and_angle(game, sprite, &distance, &angle_diff);
	if (distance <= 0.1)
		return ;
	calculate_sprite_dimensions(distance, angle_diff, render);
}
