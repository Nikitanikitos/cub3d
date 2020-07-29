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

float	fixed_angle(float angle)
{
	if (angle < 0)
		return (angle + (float)(2 * PI));
	else if (angle > (2 * PI))
		return (angle - (float)(2 * PI));
	else
		return (angle);
}

float	count_dist_to_wall(t_cub *cub, float ray_angle, float *x)
{
	t_player		player = cub->player;
	t_screen		screen = cub->screen;
	t_dist_to_wall	dist_to_wall_h;
	t_dist_to_wall	dist_to_wall_v;
	float			dist_to_wall;

	ray_angle = fixed_angle(ray_angle);
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
