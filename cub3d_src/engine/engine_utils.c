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

char	check_wall(t_player *player, float step_x, float step_y, int length_line)
{
	char				*map = player->map;
	const short			coor_x = (short)((player->position_x + step_x) / 64);
	const short			coor_y = (short)((player->position_y + step_y) / 64);

	if (map[coor_x + coor_y * length_line] != '1')
		return (1);
	return (0);
}

void	change_position(int key, t_player *player, t_map_data *map_data)
{
	const float	coss = cosf(player->pov);
	const float	sinn = sinf(player->pov);
	const int	length_line = map_data->length_line;

	if (key == KEY_W && check_wall(player, -coss * 8, -sinn * 8, length_line))
	{
		player->position_x -= coss * 4;
		player->position_y -= sinn * 4;
	}
	else if (key == KEY_S && check_wall(player, coss * 8, sinn * 8, length_line))
	{
		player->position_x += coss * 4;
		player->position_y += sinn * 4;
	}
	else if (key == KEY_D && check_wall(player, sinn * 8, -coss * 8, length_line))
	{
		player->position_x += sinn * 4;
		player->position_y -= coss * 4;
	}
	else if (key == KEY_A && check_wall(player, -sinn * 8, coss * 8, length_line))
	{
		player->position_x -= sinn * 4;
		player->position_y += coss * 4;
	}
}

void	change_pov(int key, t_player *player)
{
	if (key == KEY_Q)
		player->pov -= PI_DIVIDED_180 * 5;
	else if (key == KEY_E)
		player->pov += PI_DIVIDED_180 * 5;
	if (player->pov >= (2.f * PI))
		player->pov -= (float)(2.f * PI);
	else if (player->pov <= 0)
		player->pov += (float)(2.f * PI);
}

void	counting_player_coordinate(char *map, t_player *player, int length_line)
{
	unsigned char	count_line;
	unsigned short	x;
	unsigned short	y;

	y = 0;
	x = 0;
	count_line = 0;
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
