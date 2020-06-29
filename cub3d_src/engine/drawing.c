/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 01:19:07 by imicah            #+#    #+#             */
/*   Updated: 2020/06/30 01:19:08 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	drawing_floor(t_player *player, short wall_x, float distance_to_wall)
{
	const int	color = player->map_data->floor_color;
	const short	draw_limit = (short)distance_to_wall;
	short		wall_y;

	wall_y = 0;
	while (wall_y < draw_limit)
	{
		mlx_pixel_put(player->mlx, player->win, wall_x, wall_y, color);
		wall_y++;
	}
}

void	drawing_celling(t_player *player, short wall_x, float wall_y)
{
	const int	color = player->map_data->celling_color;
	const int	draw_limit = player->map_data->resolution[1];
	short 		y;

	y = (short)wall_y;
	while (y < draw_limit)
	{
		mlx_pixel_put(player->mlx, player->win, wall_x, y, color);
		y++;
	}
}

float	drawing_wall(t_player *player, short wall_x, float wall_y, short height)
{
	short y;

	y = (short)wall_y;
	while (height > 0)
	{
		mlx_pixel_put(player->mlx, player->win, wall_x, y, 0x800080);
		y++;
		height--;
	}
	return (y);
}