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

float		get_step_x_vertical(float ray_angle)
{
	if (ray_angle < (M_PI / 2) || ray_angle > (3 * M_PI / 2))
		return (CELL);
	else
		return (-CELL);
}

float		get_x_vertical(float position, float angle)
{
	float	x;

	x = (float)((int)(position / CELL) * CELL);
	x += (angle < (M_PI / 2) || angle > (3 * M_PI / 2)) ? CELL : -.01f;
	return (x);
}

float		get_y_vertical(t_player player, float x, float angle)
{
	return (player.y + (player.x - x) * tanf(angle));
}

t_distance	dist_to_wall_vertical(t_player player, float ray_angle, int height)
{
	const float		step_x = get_step_x_vertical(ray_angle);
	const float		step_y = -step_x * tanf(ray_angle);
	t_map			map;
	t_coordinates	current;
	t_distance		distance;

	map = player.map;
	current.x = get_x_vertical(player.x, ray_angle);
	current.y = get_y_vertical(player, current.x, ray_angle);
	map.x = (int)(current.x / CELL);
	map.y = (int)(current.y / CELL);
	while (map.y > 0 && map.y < map.column_length)
	{
		map.x = (int)(current.x / CELL);
		map.y = (int)(current.y / CELL);
		if (map.map[map.x + map.y * map.line_length] == '1')
			break ;
		current.x += step_x;
		current.y += step_y;
	}
	distance.x = get_texture_x(current.y);
	distance.distance = get_distance(player.x - current.x, player.y - current.y);
	return (distance);
}
