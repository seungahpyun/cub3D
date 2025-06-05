/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_renderer.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/03 11:11:51 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 11:27:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static int	get_max_frames(t_sprite_type type)
{
	if (type == SPRITE_TREE)
		return (TREE_FRAMES);
	return (1);
}

static void	update_single_sprite_animation(t_sprite *sprite,
										double current_time)
{
	int		max_frames;
	double	time_diff;

	max_frames = get_max_frames(sprite->type);
	time_diff = current_time - sprite->last_frame_time;
	if (time_diff >= SPRITE_ANIMATION_SPEED)
	{
		sprite->current_frame++;
		if (sprite->current_frame >= max_frames)
			sprite->current_frame = 0;
		sprite->last_frame_time = current_time;
	}
}

void	update_sprite_animations(t_game *game)
{
	int		i;
	double	current_time;

	current_time = mlx_get_time();
	i = 0;
	while (i < game->map.sprite_count)
	{
		update_single_sprite_animation(&game->map.sprites[i], current_time);
		i++;
	}
}

void	calculate_sprite_distances(t_game *game)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < game->map.sprite_count)
	{
		dx = game->map.sprites[i].x - game->player.x;
		dy = game->map.sprites[i].y - game->player.y;
		game->map.sprites[i].distance = sqrt(dx * dx + dy * dy);
		i++;
	}
}

static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_sprites_by_distance(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.sprite_count - 1)
	{
		j = 0;
		while (j < game->map.sprite_count - i - 1)
		{
			if (game->map.sprites[j].distance
				< game->map.sprites[j + 1].distance)
			{
				swap_sprites(&game->map.sprites[j], &game->map.sprites[j + 1]);
			}
			j++;
		}
		i++;
	}
}

static void	calculate_sprite_screen_pos(t_game *game, t_sprite *sprite,
									t_sprite_render *render)
{
	double	dx;
	double	dy;
	double	distance;
	double	sprite_angle;
	double	angle_diff;

	dx = sprite->x - game->player.x;
	dy = sprite->y - game->player.y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance <= 0.1)
		return ;
	sprite_angle = atan2(-dy, dx);
	angle_diff = sprite_angle - game->player.angle;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
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

static uint32_t	get_sprite_pixel(mlx_image_t *texture, int tex_x, int tex_y)
{
	int			pixel_index;
	uint8_t		*pixel_ptr;
	uint32_t	color;

	if (!texture || !texture->pixels)
		return (0);
	if (tex_x < 0 || tex_x >= (int)texture->width
		|| tex_y < 0 || tex_y >= (int)texture->height)
		return (0);
	pixel_index = (tex_y * texture->width + tex_x) * 4;
	pixel_ptr = texture->pixels + pixel_index;
	color = (pixel_ptr[0] << 24) | (pixel_ptr[1] << 16)
		| (pixel_ptr[2] << 8) | pixel_ptr[3];
	return (color);
}

static void	draw_sprite_column(t_game *game, t_sprite *sprite,
							t_sprite_render *render, int stripe)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	mlx_image_t	*texture;

	texture = sprite->frames[sprite->current_frame];
	if (!texture)
		return ;
	tex_x = (int)(256 * (stripe - (-render->sprite_width / 2
					+ (int)render->screen_x)) * texture->width
			/ render->sprite_width) / 256;
	if (tex_x < 0 || tex_x >= (int)texture->width)
		return ;
	y = render->draw_start_y;
	while (y < render->draw_end_y)
	{
		tex_y = (((y * 256 - HEIGHT * 128 + render->sprite_height * 128)
					* texture->height) / render->sprite_height) / 256;
		color = get_sprite_pixel(texture, tex_x, tex_y);
		if ((color & 0xFF) > 0 && game->rays[stripe].dist > sprite->distance)
		{
			if (is_within_boundary(stripe, y, game->img->width,
					game->img->height))
				mlx_put_pixel(game->img, stripe, y, color);
		}
		y++;
	}
}

static void	render_single_sprite(t_game *game, t_sprite *sprite)
{
	t_sprite_render	render;
	int				stripe;

	if (sprite->distance <= 0)
		return ;
	calculate_sprite_screen_pos(game, sprite, &render);
	if (render.screen_x < -render.sprite_width / 2
		|| render.screen_x > WIDTH + render.sprite_width / 2)
		return ;
	stripe = render.draw_start_x;
	while (stripe < render.draw_end_x)
	{
		draw_sprite_column(game, sprite, &render, stripe);
		stripe++;
	}
}

void	render_sprites(t_game *game)
{
	int	i;

	calculate_sprite_distances(game);
	sort_sprites_by_distance(game);
	i = 0;
	while (i < game->map.sprite_count)
	{
		render_single_sprite(game, &game->map.sprites[i]);
		i++;
	}
}
