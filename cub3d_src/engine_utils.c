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

void	change_position(int key, t_player *player)
{
	const double 	coss = cos(player->pov * PI / 180);
	const double 	sinn = -sin(player->pov * PI / 180);

	if (key == KEY_W)
	{
		player->position_y += sinn * 4;
		player->position_x += coss * 4;
	}
	else if (key == KEY_S)
	{
		player->position_x -= coss * 4;
		player->position_y -= sinn * 4;
	}
	else if (key == KEY_D)
	{
		player->position_y += coss * 4;
		player->position_x -= sinn * 4;
	}
	else if (key == KEY_A)
	{
		player->position_y -= coss * 4;
		player->position_x += sinn * 4;
	}
}

void	change_pov(int key, t_player *player)
{
	if (key == 113)
		player->pov += 5;
	else if (key == 101)
		player->pov -= 5;
	if (player->pov >= 360)
		player->pov = 0;
}

void 	counting_player_coordinate(char *map, t_player *player)
{
	unsigned char 	count_line;
	unsigned short	x;
	unsigned short	y;

	y = 0;
	x = 0;
	count_line = 0;
	while (*map)
	{
		if (ft_strchr(PLAYER_POS, *map))
			player_coor_init(player, x, y, *map);
		if (++count_line == player->map_data->length_line)
		{
			y += 64;
			x = 0;
			count_line = 0;
		}
		else
			x += 64;
		map++;
	}
}