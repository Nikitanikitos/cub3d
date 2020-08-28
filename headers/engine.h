/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:43:07 by imicah            #+#    #+#             */
/*   Updated: 2020/06/25 16:43:07 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "cub3d.h"
# include <math.h>

# define PI_DIV_180		(float)(M_PI / 180.f)
# define FOV			60.f
# define FOV_RAD		FOV * PI_DIV_180

# define CELL			64
# define PLAYER_SPEED	6

# define ARROW_LEFT		65361
# define ARROW_RIGHT	65363
# define ARROW_UP		65362
# define ARROW_DOWN		65364

typedef struct	s_distance
{
	float		distance;
	float		x;
}				t_distance;

typedef struct	s_coordinates
{
	float		x;
	float		y;
}				t_coordinates;

t_player		player_init(t_game_info *game_info);
t_cub			cub_init(t_screen screen, t_player player,
														t_game_info *game_info);

void			change_position(int key, t_player *player);
void			change_pov(int key, t_player *player);

int8_t			compare_pov(t_player player, float pov, float look);
int8_t			compare_position(t_player player, float x, float y);

void			rendering_ceiling(t_cub *cub, int height, int wall_x);
void			rendering_wall(t_cub *cub, int wall_y, int height, int wall_x);
void			rendering_floor(t_cub *cub, int height, int wall_x);
void			rendering_sprites(t_game_info game_info, t_player player,
											t_screen screen, float *distances);

float			fix_angle(float angle);
int				check_transparency(t_img_data texture, int index);

void			put_pixel(t_img_data img, int index, t_color color);
void			put_pixel_img(t_img_data img, t_img_data texture, int index,
															int index_texture);

float			get_texture_coordinate(float current_x);
float			get_distance(float x, float y);
void			get_wall_texture(t_cub *cub, float ray_angle,
						float distance_to_wall_h, float distance_to_wall_v);

float			calculate_height(float distance_to_wall, t_screen screen);
void			calculate_offset(t_sprite *sprite, t_screen screen, float angle,
															t_player player);
float			calculate_direction_sprite(t_sprite sprite, t_player player,
																	float pov);

t_distance		calculate_distance_to_wall(t_cub *cub, float ray_angle);
t_distance		calculate_distance_to_wall_v(t_player player, float ray_angle);
t_distance		calculate_distance_to_wall_h(t_player player, float ray_angle);

#endif
