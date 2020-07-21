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

float	dist_to_wall_horizontal(t_map_data *map_data, t_player *player, float ray_angle)
{
	const float			step_y = (ray_angle < PI) ? -64 : 64;
	const float			step_x = -step_y * (-1 / tanf(ray_angle));
	float				current_y;
	float				current_x;

	current_y = (float)((int)(player->position_y / 64) * 64);
	current_y += (ray_angle < PI) ? -.01f : 64;
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

float	dist_to_wall_vertical(t_map_data *map_data, t_player *player, float ray_angle)
{
	const float			step_x = (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? -64 : 64;
	const float			step_y = -step_x * -tanf(ray_angle);
	float				current_y;
	float				current_x;

	current_x = (float)((int)(player->position_x / 64) * 64);
	current_x += (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? -.01f : 64;
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