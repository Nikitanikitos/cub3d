/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist_to_wall_horizontal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 13:06:56 by imicah            #+#    #+#             */
/*   Updated: 2020/07/29 13:06:57 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "engine.h"

float		get_x_horizontal(t_player player, float y, float angle)
{
	float	x;

	x = player.position_x + (player.position_y - y) *
							(-1 / tanf(angle));
	return (x);
}

float		get_y_horizontal(t_player player, float angle)
{
	float	y;

	y = (float)((int)(player.position_y / 64) * 64);
	y += (angle < PI) ? -.01f : 64;
	return (y);
}

t_distance	dist_to_wall_horizontal(t_player player, float ray_angle, int width)
{
	const t_map		map = player.map;
	const float		step_y = (ray_angle < PI) ? -64 : 64;
	const float		step_x = -step_y * (-1 / tanf(ray_angle));
	t_coordinates	current;
	t_distance		distance;

	current.y = get_y_horizontal(player, ray_angle);
	current.x = get_x_horizontal(player, current.y, ray_angle);
	while ((int)current.x > 0 && (int)current.x < width)
	{
		if (map.map[(int)(current.x / 64) + (int)(current.y / 64) * map.length_line] == '1')
			break ;
		current.x += step_x;
		current.y += step_y;
	}
	distance.x = current.x;
	if (distance.x < 0)
		distance.x = 0;
	current.x = player.position_x - current.x;
	current.y = player.position_y - current.y;
	distance.distance = sqrtf(current.x * current.x + current.y * current.y);
	return (distance);
}
