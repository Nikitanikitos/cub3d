/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 00:52:07 by imicah            #+#    #+#             */
/*   Updated: 2020/08/05 00:52:11 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int8_t	check_wall(t_player *player, float step_x, float step_y)
{
	const int	coord_x = (int)((player->x + step_x * PLAYER_SPEED * 2) / 64);
	const int	coord_y = (int)((player->y + step_y * PLAYER_SPEED * 2) / 64);
	const t_map	map = player->map;

	return (map.map[coord_x + coord_y * map.line_length] != '1' &&
			map.map[coord_x + coord_y * map.line_length] != '2');
}

void	change_position(int key, t_player *player)
{
	const float	coss = cosf(player->pov);
	const float	sinn = -sinf(player->pov);

	if (key == XK_w && check_wall(player, coss, sinn))
	{
		player->x += coss * PLAYER_SPEED;
		player->y += sinn * PLAYER_SPEED;
	}
	else if (key == XK_s && check_wall(player, -coss, -sinn))
	{
		player->x -= coss * PLAYER_SPEED;
		player->y -= sinn * PLAYER_SPEED;
	}
	else if (key == XK_d && check_wall(player, -sinn, coss))
	{
		player->x -= sinn * PLAYER_SPEED;
		player->y += coss * PLAYER_SPEED;
	}
	else if (key == XK_a && check_wall(player, sinn, -coss))
	{
		player->x += sinn * PLAYER_SPEED;
		player->y -= coss * PLAYER_SPEED;
	}
}

void	change_crouch(t_player *player)
{
	if (player->crouch == 0)
		player->crouch = -50;
	else
		player->crouch = 0;
}

void	change_pov(int key, t_player *player)
{
	if (key == ARROW_LEFT)
		player->pov += PI_DIV_180 * 5;
	else if (key == ARROW_RIGHT)
		player->pov -= PI_DIV_180 * 5;
	else if (key == ARROW_UP)
		player->look += 10;
	else if (key == ARROW_DOWN)
		player->look -= 10;
	player->pov = fix_angle(player->pov);
}
