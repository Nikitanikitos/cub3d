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

#include "engine.h"

void	dist_to_wall_horizontal(t_player player, t_dist_to_wall *distance,
								float ray_angle, int width)
{
	const t_map			map = player.map;
	const float			step_y = (ray_angle < PI) ? -64 : 64;
	const float			step_x = -step_y * (-1 / tanf(ray_angle));
	float				y;
	float				x;

	y = (float)((int)(player.position_y / 64) * 64);
	y += (ray_angle < PI) ? -.01f : 64;
	x = player.position_x + (player.position_y - y) *
							 (-1 / tanf(ray_angle));
	while ((int)x > 0 && (int)x < width)
	{
		if (map.map[(int)(x / 64) + (int)(y / 64) * map.length_line] == '1')
			break ;
		x += step_x;
		y += step_y;
	}
	distance->x = (int)x;
	x = player.position_x - x;
	y = player.position_y - y;
	distance->distance = sqrtf(x * x + y * y);
}

float	get_step_x_vertical(float ray_angle)
{
	if (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2))
		return (-64);
	else
		return (64);
}

void	dist_to_wall_vertical(t_player player, t_dist_to_wall *distance,
							  float ray_angle, int height)
{
	t_map		map = player.map;
	const float	step_x = get_step_x_vertical(ray_angle);
	const float	step_y = -step_x * -tanf(ray_angle);
	float		y;
	float		x;

	x = (float)((int)(player.position_x / 64) * 64);
	x += (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? -.01f : 64;
	y = player.position_y + (player.position_x - x) * -tanf(ray_angle);
	while ((int)y > 0 && (int)y < height)
	{
		if (map.map[(int)(x / 64) + (int)(y / 64) * map.length_line] == '1')
			break ;
		x += step_x;
		y += step_y;
	}
	distance->x = (int)y;
	if (distance->x < 0)
		distance->x = 0;
	x = (player.position_x - x);
	y = (player.position_y - y);
	distance->distance = sqrtf(x * x + y * y);
}

float	count_dist_to_wall(t_cub *cub,
							float ray_angle, float *x)
{
	t_player		player = cub->player;
	t_screen		screen = cub->screen;
	t_dist_to_wall	dist_to_wall_h;
	t_dist_to_wall	dist_to_wall_v;
	float			dist_to_wall;

	ray_angle += (ray_angle < 0) ? (float)(2 * PI) : 0;
	ray_angle -= (ray_angle > (2 * PI)) ? (float)(2 * PI) : 0;
	dist_to_wall_horizontal(player, &dist_to_wall_h, ray_angle, screen.resolution[0]);
	dist_to_wall_vertical(player, &dist_to_wall_v, ray_angle, screen.resolution[1]);
	if (dist_to_wall_h.distance > dist_to_wall_v.distance)
	{
		*x = modff((float)dist_to_wall_v.x / 64, &dist_to_wall);
		dist_to_wall = dist_to_wall_v.distance * cosf(player.pov - ray_angle);
	}
	else
	{
		*x = modff((float)dist_to_wall_h.x / 64, &dist_to_wall);
		dist_to_wall = dist_to_wall_h.distance * cosf(player.pov - ray_angle);
	}
	get_wall_texture(cub, ray_angle, dist_to_wall_h.distance, dist_to_wall_v.distance);
	return (dist_to_wall);
}
