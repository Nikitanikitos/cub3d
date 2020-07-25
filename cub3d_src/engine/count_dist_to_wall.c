/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_dist_to_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 01:44:16 by imicah            #+#    #+#             */
/*   Updated: 2020/07/22 01:44:18 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"

float	count_dist_to_wall(t_map_data *map_data, t_player *player,
						float ray_angle, float *x)
{
	t_dist_to_wall	dist_to_wall_h;
	t_dist_to_wall	dist_to_wall_v;
	float			dist_to_wall;

	ray_angle += (ray_angle < 0) ? (float)(2 * PI) : 0;
	ray_angle -= (ray_angle > (2 * PI)) ? (float)(2 * PI) : 0;
	dist_to_wall_horizontal(*map_data, *player, ray_angle, &dist_to_wall_h);
	dist_to_wall_vertical(*map_data, *player, ray_angle, &dist_to_wall_v);
	if (dist_to_wall_h.distance > dist_to_wall_v.distance)
	{
		*x = modff((float)dist_to_wall_v.x / 64, &dist_to_wall);
		dist_to_wall = dist_to_wall_v.distance * cosf(player->pov - ray_angle);
	}
	else
	{
		*x = modff((float)dist_to_wall_h.x / 64, &dist_to_wall);
		dist_to_wall = dist_to_wall_h.distance * cosf(player->pov - ray_angle);
	}
	get_wall_texture(map_data, ray_angle, dist_to_wall_h.distance, dist_to_wall_v.distance);
	return (dist_to_wall);
}

void	dist_to_wall_horizontal(t_map_data map_data, t_player player,
							float ray_angle, t_dist_to_wall *distance)
{
	const float			step_y = (ray_angle < PI) ? -64 : 64;
	const float			step_x = -step_y * (-1 / tanf(ray_angle));
	const int 			length_line = map_data.length_line;
	float				y;
	float				x;

	y = (float)((int)(player.position_y / 64) * 64);
	y += (ray_angle < PI) ? -.01f : 64;
	x = player.position_x + (player.position_y - y) *
							 (-1 / tanf(ray_angle));
	while ((int)x > 0 && (int)x < map_data.resolution[0])
	{
		if (map_data.map[(int)(x / 64) + (int)(y / 64) * length_line] == '1')
			break ;
		x += step_x;
		y += step_y;
	}
	distance->x = (int)x;
	x = player.position_x - x;
	y = player.position_y - y;
	distance->distance = sqrtf(x * x + y * y);
}

void	dist_to_wall_vertical(t_map_data map_data, t_player player,
							float ray_angle, t_dist_to_wall *distance)
{
	const int	length_line = map_data.length_line;
	float		step_x;
	float		step_y;
	float		y;
	float		x;

	step_x = (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? -64 : 64;
	step_y = -step_x * -tanf(ray_angle);
	x = (float)((int)(player.position_x / 64) * 64);
	x += (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? -.01f : 64;
	y = player.position_y + (player.position_x - x) * -tanf(ray_angle);
	while ((int)y > 0 && (int)y < map_data.resolution[1])
	{
		if (map_data.map[(int)(x / 64) + (int)(y / 64) * length_line] == '1')
			break ;
		x += step_x;
		y += step_y;
	}
	distance->x = (int)y;
	x = (player.position_x - x);
	y = (player.position_y - y);
	distance->distance = sqrtf(x * x + y * y);
}