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
#include "stdio.h"

char	check_wall(t_player *player, double step_x, double step_y)
{
	const t_map_data	*map_data = player->map_data;
	const double		coor_x = player->position_x + step_x;
	const double		coor_y = player->position_y + step_y;

	if (map_data->map[(int)coor_x / 64 +
						(int)coor_y / 64 * map_data->length_line] != '1')
		return (1);
	return (0);
}

void	change_position(int key, t_player *player)
{
	const double	coss = cos(player->pov * PI / 180);
	const double	sinn = -sin(player->pov * PI / 180);

	if (key == KEY_W && check_wall(player, coss * 4, sinn * 4))
	{
		player->position_x += coss * 4;
		player->position_y += sinn * 4;
	}
	else if (key == KEY_S && check_wall(player, -coss * 4, -sinn * 4))
	{
		player->position_x -= coss * 4;
		player->position_y -= sinn * 4;
	}
	else if (key == KEY_D && check_wall(player, -sinn * 4, coss * 4))
	{
		player->position_x -= sinn * 4;
		player->position_y += coss * 4;
	}
	else if (key == KEY_A && check_wall(player, sinn * 4, -coss * 4))
	{
		player->position_x += sinn * 4;
		player->position_y -= coss * 4;
	}
}

void	change_pov(int key, t_player *player)
{
	if (key == KEY_Q)
		player->pov += 5;
	else if (key == KEY_E)
		player->pov -= 5;
	if (player->pov >= 360)
		player->pov = 0;
	else if (player->pov <= 0)
		player->pov = 360;
}

void	counting_player_coordinate(char *map, t_player *player)
{
	unsigned char	count_line;
	unsigned char	length_line;
	unsigned short	x;
	unsigned short	y;

	y = 0;
	x = 0;
	count_line = 0;
	length_line = player->map_data->length_line;
	while (*map)
	{
		if (ft_strchr(PLAYER_POS, *map))
			player_coor_init(player, x, y, *map);
		if (++count_line == length_line)
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
