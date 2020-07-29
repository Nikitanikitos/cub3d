/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall_vertical.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 13:00:36 by imicah            #+#    #+#             */
/*   Updated: 2020/07/29 13:00:37 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "engine.h"

float	get_step_x_vertical(float ray_angle)
{
	if (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2))
		return (-64);
	else
		return (64);
}

float	get_x_vertical(float position, float angle)
{
	float	x;

	x = (float)((int)(position / 64) * 64);
	x += (angle < (PI / 2) || angle > (3 * PI / 2)) ? -.01f : 64;
	return (x);
}

float	get_y_verticatal(t_player player, float x, float angle)
{
	float	y;

	y = player.position_y + (player.position_x - x) * -tanf(angle);
	return (y);
}

t_dist_to_wall	dist_to_wall_vertical(t_player player, float ray_angle, int height)
{
	t_map			map = player.map;
	const float		step_x = get_step_x_vertical(ray_angle);
	const float		step_y = -step_x * -tanf(ray_angle);
	t_coordinates	current;
	t_dist_to_wall	distance;

	current.x = get_x_vertical(player.position_x, ray_angle);
	current.y = get_y_verticatal(player, current.x, ray_angle);
	while ((int)current.y > 0 && (int)current.y < height)
	{
		if (map.map[(int)(current.x / 64) + (int)(current.y / 64) * map.length_line] == '1')
			break ;
		current.x += step_x;
		current.y += step_y;
	}
	distance.x = (int)current.y;
	if (distance.x < 0)
		distance.x = 0;
	current.x = (player.position_x - current.x);
	current.y = (player.position_y - current.y);
	distance.distance = sqrtf(current.x * current.x + current.y * current.y);
	return (distance);
}
