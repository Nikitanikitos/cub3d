/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 15:59:41 by imicah            #+#    #+#             */
/*   Updated: 2020/06/16 15:59:42 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"

float count_distance_to_wall(t_player *player, float corner, t_map_data *map_data)
{
	const float		step_x = cosf(corner);
	const float		step_y = -sinf(corner);
	float			dist;
	float			current_y;
	float			current_x;

	dist = 0;
	current_x = player->position_x;
	current_y = player->position_y;
	while (True)
	{
		current_y += step_y;
		current_x += step_x;
		if (map_data->map[(int)current_x / 64 + (int)current_y / 64 *
												map_data->length_line] == '1')
			break ;
		dist++;
	}
	return (dist * cosf(player->pov - corner));
}

//float	distance_to_wall_horizontal(t_player *player, float corner_ray)
//{
//	const t_map_data	*map_data = player->map_data;
//	const float			step_y = (corner_ray <= PI) ? -64 : 64;
//	const float			step_x = 64 / tanf(corner_ray);
//	float				current_y;
//	float				current_x;
//
//	current_y = (int)(player->position_y / 64) * 64;
//	current_y += (corner_ray <= PI) ? -1 : 64;
//	current_x = player->position_x + (player->position_y - current_y) /
//																tanf(corner_ray);
//	while ((int)current_x > 0 && (int)current_y > 0 &&
//		   (int)current_y < map_data->resolution[1] && (int)current_x < map_data->resolution[0])
//	{
//		if (map_data->map[(int)(current_x / 64) + (int)(current_y / 64) *
//												map_data->length_line] == '1')
//			break ;
//		current_x += step_x;
//		current_y += step_y;
//	}
//	printf("current_x - %f current_y - %f\n", current_x, current_y);
//	current_x = player->position_x - current_x;
//	current_y = player->position_y - current_y;
//	return (sqrtf(current_x * current_x + current_y * current_y));
//}

//float	distance_to_wall_vertical(t_player *player, float corner_ray)
//{
//	const t_map_data	*map_data = player->map_data;
//	const float			step_x = (corner_ray <= (PI / 2) || corner_ray >= (3 * PI / 2)) ? 64 : -64;
//	const float			step_y = -step_x * tanf(corner_ray);
//	float				current_y;
//	float				current_x;
//
//	current_x = (int)(player->position_x / 64) * 64;
//	current_x += (corner_ray <= (PI / 2) || corner_ray >= (3 * PI / 2)) ? 64 : -0.0001;
//	current_y = player->position_y + (player->position_x - current_x) *
//																tanf(corner_ray);
//	while ((int)current_x > 0 && (int)current_y > 0 &&
//		   (int)current_y < map_data->resolution[1] && (int)current_x < map_data->resolution[0])
//	{
//		if (map_data->map[(int)(current_x / 64) + (int)(current_y / 64) *
//												map_data->length_line] == '1')
//			break ;
//		current_x += step_x;
//		current_y += step_y;
//	}
//	current_x = (player->position_x - current_x);
//	current_y = (player->position_y - current_y);
//	return (sqrtf(current_x * current_x + current_y * current_y));
//}

float	dist_to_wall_horizontal(t_player *player, float ray_angle)
{
	const t_map_data	*map_data = player->map_data;
	const float			step_y = (ray_angle > PI) ? -64 : 64;
	const float			step_x = -step_y * (-1 / tanf(ray_angle));
	float				current_y;
	float				current_x;

	current_y = (float)((int)(player->position_y / 64) * 64);
	current_y += (ray_angle > PI) ? -.01f : 64;
	current_x = player->position_x + (player->position_y - current_y) *
									 (-1 / tanf(ray_angle));
	while ((int)current_x > 0 && (int)current_y > 0 &&
		   (int)current_y < map_data->resolution[1] && (int)current_x < map_data->resolution[0])
	{
		if (map_data->map[(int)(current_x / 64) + (int)(current_y / 64) *
												  map_data->length_line] == '1')
			break ;
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrtf(current_x * current_x + current_y * current_y));
}

float	dist_to_wall_vertical(t_player *player, float ray_angle)
{
	const t_map_data	*map_data = player->map_data;
	const float			step_x = (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? 64 : -64;
	const float			step_y = -step_x * -tanf(ray_angle);
	float				current_y;
	float				current_x;

	current_x = (float)((int)(player->position_x / 64) * 64);
	current_x += (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? 64 : -.01f;
	current_y = player->position_y + (player->position_x - current_x) *
									 -tanf(ray_angle);
	while ((int)current_x > 0 && (int)current_y > 0 &&
		   (int)current_y < map_data->resolution[1] && (int)current_x < map_data->resolution[0])
	{
		if (map_data->map[(int)(current_x / 64) + (int)(current_y / 64) *
												  map_data->length_line] == '1')
			break ;
		current_x += step_x;
		current_y += step_y;
	}
	current_x = (player->position_x - current_x);
	current_y = (player->position_y - current_y);
	return (sqrtf(current_x * current_x + current_y * current_y));
}

void	cast_ray_3d(t_player *player, float ray_angle, short wall_x)
{
	const t_map_data	*map_data = player->map_data;
	short				height;
	float				dist_to_wall;
	float				dist_to_wall_h;
	float				dist_to_wall_v;

	if (ray_angle < 0)
		ray_angle += (float)(2 * PI);
	else if (ray_angle > (2 * PI))
		ray_angle -= (float)(2 * PI);

	dist_to_wall_h = dist_to_wall_horizontal(player, ray_angle);
	dist_to_wall_v = dist_to_wall_vertical(player, ray_angle);

	if (dist_to_wall_h > dist_to_wall_v)
		dist_to_wall = dist_to_wall_v * cosf(player->pov - ray_angle);
	else
		dist_to_wall = dist_to_wall_h * cosf(player->pov - ray_angle);

	height = (short)(64 / dist_to_wall * ((float)map_data->resolution[0] /
														2 / tanf(FOV_RAD / 2)));
	dist_to_wall = (float)map_data->resolution[1] / 2 - (float)height / 2;
	drawing_floor(player, wall_x, dist_to_wall);
	dist_to_wall = drawing_wall(player, wall_x, dist_to_wall, height);
	drawing_celling(player, wall_x, dist_to_wall);
}

void	field_of_view_3d(t_player *player)
{
	const float		last_corner = player->pov + (FOV_RAD / 2);
	float			step;
	float			ray_angle;
	short			wall_x;

	step = (FOV / (float)player->map_data->resolution[0]) * PI_DIVIDED_180;
	ray_angle = player->pov - (FOV_RAD / 2);
	wall_x = player->map_data->resolution[0];
	while (ray_angle <= last_corner)
	{
		cast_ray_3d(player, ray_angle, wall_x);
		ray_angle += step;
		wall_x--;
	}
}

int		game_play(int key, t_player *player)
{
	if (key == KEY_E || key == KEY_Q)
		change_pov(key, player);
	else if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W)
		change_position(key, player);
	field_of_view_3d(player);
	return (0);
}

int		engine(t_map_data *map_data)
{
	t_player	*player;
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	win = mlx_new_window(
			mlx, map_data->resolution[0], map_data->resolution[1], "Cub3D");
	player = player_init(mlx, win, map_data);
	counting_player_coordinate(map_data->map, player);
	field_of_view_3d(player);
	mlx_hook(win, 2, 1L << 0, game_play, player);
//	mlx_key_hook(win, game_play, player);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
