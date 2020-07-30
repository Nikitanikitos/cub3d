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

# define PI				3.14159265359
# define PI_DIV_180		(float)(PI / 180)
# define FOV			60.f
# define FOV_RAD		FOV * PI_DIV_180

# define CELL			64

# define KEY_W			119
# define KEY_S			115
# define KEY_D			100
# define KEY_A			97
# define KEY_Q			113
# define KEY_E			101

typedef struct	s_distance
{
	float		distance;
	float 		x;
}				t_distance;

typedef struct	s_coordinates
{
	float		x;
	float		y;
}				t_coordinates;

t_cub			cub_init(t_screen screen, t_game_info *game_info);

void			change_position(int key, t_player *player);
void			change_pov(int key, t_player *player);
void			print_map(void *win, t_xvar *mlx, char *map, t_player *player);
void			field_of_view(t_player *player, int color);

void			drawing_floor(t_cub *cub, int height, int wall_x);
void			drawing_wall(t_cub *cub, int wall_y, int height, int wall_x);
void			drawing_celling(t_cub *cub, int height, int wall_x);
void			drawing_items(t_game_info game_info, t_player player, t_screen screen);

float	count_height_wall(float dist_to_wall, t_screen screen);


void			get_wall_texture(t_cub *cub, float ray_angle,
								 float dist_to_wall_h, float dist_to_wall_v);

float			get_texture_x(float current_x);
float			get_distance(float x, float y);

t_distance		dist_to_wall_vertical(t_player player, float ray_angle, int height);
t_distance		dist_to_wall_horizontal(t_player player, float ray_angle, int width);
t_distance		count_dist_to_wall(t_cub *cub, float ray_angle);

#endif
