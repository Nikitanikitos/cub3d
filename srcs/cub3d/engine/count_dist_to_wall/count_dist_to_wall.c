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

t_distance	dist_to_wall_init(t_distance dist_to_wall, float pov, float angle)
{
	t_distance	distance;

	distance.x = modff(dist_to_wall.x / CELL, &dist_to_wall.x);
	distance.distance = dist_to_wall.distance * cosf(pov - angle);
	return (distance);
}

float		fixed_angle(float angle)
{
	if (angle < 0)
		return (angle + (float)(2 * M_PI));
	else if (angle > (2 * M_PI))
		return (angle - (float)(2 * M_PI));
	else
		return (angle);
}

t_distance	count_dist_to_wall(t_cub *cub, float ray_angle)
{
	t_player	player = cub->player;
	t_screen	screen = cub->screen;
	t_distance	dist_to_wall_h;
	t_distance	dist_to_wall_v;

	ray_angle = fixed_angle(ray_angle);

	dist_to_wall_h = dist_to_wall_horizontal(player, ray_angle, screen.width);
	dist_to_wall_v = dist_to_wall_vertical(player, ray_angle, screen.height);
	get_wall_texture(cub, ray_angle, dist_to_wall_h.distance, dist_to_wall_v.distance);
	if (dist_to_wall_h.distance > dist_to_wall_v.distance)
		return (dist_to_wall_init(dist_to_wall_v, player.pov, ray_angle));
	else
		return (dist_to_wall_init(dist_to_wall_h, player.pov, ray_angle));
}
