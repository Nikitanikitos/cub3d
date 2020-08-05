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
	return (player.x + (player.y - y) * (1 / tanf(angle)));
}

float		get_y_horizontal(t_player player, float angle)
{
	float	y;

	y = (float)((int)(player.y / CELL) * CELL);
	y += (angle < M_PI) ? -.01f : CELL;
	return (y);
}

t_distance	dist_to_wall_horizontal(t_player player, float ray_angle, int width)
{
	const float		step_y = (ray_angle < M_PI) ? -CELL : CELL;
	const float		step_x = -step_y * (1 / tanf(ray_angle));
	t_map			map;
	t_coordinates	current;
	t_distance		distance;

	map = player.map;
	current.y = get_y_horizontal(player, ray_angle);
	current.x = get_x_horizontal(player, current.y, ray_angle);
	map.x = (int)(current.x / CELL);
	map.y = (int)(current.y / CELL);
	while (map.x > 0 && map.x < map.line_length)
	{
		map.x = (int)(current.x / CELL);
		map.y = (int)(current.y / CELL);
		if (map.map[map.x + map.y * map.line_length] == '1')
			break ;
		current.x += step_x;
		current.y += step_y;
	}
	distance.x = get_texture_x(current.x);
	distance.distance = get_distance(player.x - current.x, player.y - current.y);
	return (distance);
}
