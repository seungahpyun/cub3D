/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/19 09:43:55 by spyun         #+#    #+#                 */
/*   Updated: 2025/06/05 14:34:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define MINIMAP_RADIUS 10
# define MINIMAP_CELL_SIZE 16
# define MINIMAP_W (MINIMAP_RADIUS * 2 + 1) * MINIMAP_CELL_SIZE
# define MINIMAP_H MINIMAP_W
# define MINIMAP_GRID (MINIMAP_RADIUS * 2 + 1)

# define MINIMAP_WALL_COLOR 0xFFAA96B2
# define MINIMAP_FLOOR_COLOR 0xFFEFE7D3
# define MINIMAP_PLAYER_COLOR 0x65965EFF// light green
# define MINIMAP_EMPTY_COLOR 0x00000000
# define MINIMAP_RAY_COLOR 0xFAAC96
# define MINIMAP_SPRITE_COLOR 0xFF00FFFF

# define RED 0xFF0000FF
# define DEFAULT_TEXTURE_COLOR 0x001f1f1f

# define HIT_SIDE_VERTICAL 'v'
# define HIT_SIDE_HORIZONTAL 'h'

# define FOV 60.0
# define MIN_PER_DIST 0.0001

# define SPRITE_ANIMATION_SPEED 0.15

# include "common.h"

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_cell
{
	int		px;
	int		py;
	int		size;
	int		color;
}			t_cell;

typedef struct s_ray
{
	double	start_x;
	double	start_y;
	int		map_x;
	int		map_y;
	double	angle;
	double	dir_x;
	double	dir_y;
	double	dist_inc_x;
	double	dist_inc_y;
	int		step_x;
	int		step_y;
	double	dist_to_v;
	double	dist_to_h;
	char	hit_side;
}			t_ray;

typedef struct s_wall_params
{
	int		full_wall_height;
	int		wall_top;
	int		wall_bottom;
}			t_wall_params;

typedef struct s_wall_info
{
	char	hit_side;
	double	ray_angle;
	double	hit_x;
	double	hit_y;
}			t_wall_info;

typedef struct s_texture_data
{
	mlx_image_t		*texture;
	double			wall_x;
	int				tex_x;
	t_wall_params	params;
}					t_texture_data;

typedef struct s_render_data
{
	double		per_dist;
	int			line_height;
	int			x;
	t_point		draw_start;
	t_point		draw_end;
	t_wall_info	wall_info;
}				t_render_data;

typedef struct s_sprite_render
{
	double	screen_x;
	double	screen_y;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
}			t_sprite_render;

typedef struct s_sprite_draw_data
{
	t_sprite		*sprite;
	t_sprite_render	*render;
	int				tex_x;
	int				stripe;
}					t_sprite_draw_data;

/* utils */
int			is_within_boundary(int x, int y, int width, int height);
bool		is_valid_point(t_map *map, int mx, int my);
int			get_color(char c);
double		degree_to_radian(double degree);
int			color_to_rgba(t_color *color, int a);

/*render*/
void		render(t_game *game);
void		setup_for_raycasting(t_game *game);

/* draw_primitives */
void		draw_line(mlx_image_t *img, t_point start, t_point end, int color);
void		draw_cell(mlx_image_t *img, t_cell cell);

/* cast_rays*/
void		init_ray(t_player *player, double ray_angle, t_ray *ray);
double		cast_ray(t_map *map, t_ray *ray);
/* ========================================================================== */
/*                               MINIMAP RENDERING                            */
/* ========================================================================== */
/* minimap_render*/
void		render_minimap(t_game *game);
void		render_3d_projection(t_game *game);
void		draw_ceiling(mlx_image_t *img, t_point wall_start, t_color *color);
void		draw_floor(mlx_image_t *img, t_point wall_end, t_color *color);
void		create_wall_info(t_game *game, int i, t_wall_info *wall_info,
				double ray_dist);
/* minimap_grid.c */
void		draw_minimap_grid(t_map *map, t_minimap *minimap);
void		draw_minimap_sprites(t_map *map, t_minimap *minimap);
/* minimap_player.c */
void		draw_minimap_rays(t_ray_data *rays, t_minimap *minimap);
void		draw_minimap_player(t_player *player, t_minimap *minimap);
/* ========================================================================== */
/*                               SPRITE RENDERING                             */
/* ========================================================================== */
/* sprite_animation.c */
void		update_sprite_animations(t_game *game);
/* sprite_drawing.c */
void		draw_sprite_column(t_game *game, t_sprite *sprite,
				t_sprite_render *render, int stripe);
void		calculate_sprite_screen_pos(t_game *game, t_sprite *sprite,
				t_sprite_render *render);
/* sprite_loader.c */
bool		load_all_sprites(t_game *game);
/* sprite_renderer.c */
void		render_sprites(t_game *game);
/* sprite_sorting.c */
void		calculate_sprite_distances(t_game *game);
void		sort_sprites_by_distance(t_game *game);
/* ========================================================================== */
/*                               TEXTURE RENDERING                            */
/* ========================================================================== */
/* texture_loader.c */
bool		load_textures(t_game *game);
/* texture_pixel.c */
void		draw_wall_pixels(t_game *game, int x, t_point wall_start,
				t_texture_data *data);
/* texture_renderer.c */
void		draw_textured_wall(t_game *game, t_render_data *render_data);
/* ========================================================================== */
/*                               UTILS                                         */
/* ========================================================================== */
/* pixel_utils.c */
uint32_t	get_pixel_color(mlx_image_t *texture, int tex_x, int tex_y);

#endif
