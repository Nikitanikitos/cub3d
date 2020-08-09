/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:42:02 by imicah            #+#    #+#             */
/*   Updated: 2020/06/25 16:42:03 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

float	fix_angle(float angle)
{
	if (angle <= 0)
		return (angle + (float)(2 * M_PI));
	else if (angle >= (2 * M_PI))
		return (angle - (float)(2 * M_PI));
	else
		return (angle);
}

float	calculate_height(float distance_to_wall, t_screen screen)
{
	float			height;

	height = CELL / distance_to_wall * ((float)screen.width / 2
										/ tanf(FOV_RAD / 2));
	return (height);
}

void	get_wall_texture(t_cub *cub, float ray_angle, float distance_to_wall_h,
													float distance_to_wall_v)
{
	if (distance_to_wall_h < distance_to_wall_v)
	{
		if (ray_angle < M_PI)
			cub->wall_texture.img_data = cub->game_info.textures[0];
		else
			cub->wall_texture.img_data = cub->game_info.textures[2];
	}
	else
	{
		if (ray_angle > M_PI / 2 && ray_angle < M_PI * 3 / 2)
			cub->wall_texture.img_data = cub->game_info.textures[1];
		else
			cub->wall_texture.img_data = cub->game_info.textures[3];
	}
}
