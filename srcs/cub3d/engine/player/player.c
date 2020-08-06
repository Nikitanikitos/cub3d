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

# include "engine.h"

char	check_wall(t_player *player, float step_x, float step_y)
{
	const int	coor_x = (int)((player->x + step_x) / 64);
	const int	coor_y = (int)((player->y + step_y) / 64);
	t_map		map = player->map;

	return (char)(map.map[coor_x + coor_y * map.line_length] != '1' &&
			map.map[coor_x + coor_y * map.line_length] != '2');
}

void	change_position(int key, t_player *player)
{
	const float	coss = cosf(player->pov);
	const float	sinn = -sinf(player->pov);

	if (key == XK_w && check_wall(player, coss * 8, sinn * 8))
	{
		player->x += coss * 4;
		player->y += sinn * 4;
	}
	else if (key == XK_s && check_wall(player, -coss * 8, -sinn * 8))
	{
		player->x -= coss * 4;
		player->y -= sinn * 4;
	}
	else if (key == XK_d && check_wall(player, -sinn * 8, coss * 8))
	{
		player->x -= sinn * 4;
		player->y += coss * 4;
	}
	else if (key == XK_a && check_wall(player, sinn * 8, -coss * 8))
	{
		player->x += sinn * 4;
		player->y -= coss * 4;
	}
	else if (key == XK_Control_L)
	{
		if (player->crouch == 0)
			player->crouch = -50;
		else
			player->crouch = 0;
	}

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
