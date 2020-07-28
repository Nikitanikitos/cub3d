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

char	check_wall(t_player *player, float step_x, float step_y)
{
	const int	coor_x = (int)((player->position_x + step_x) / 64);
	const int	coor_y = (int)((player->position_y + step_y) / 64);
	t_map		map = player->map;

	return (char)(map.map[coor_x + coor_y * map.length_line] != '1');
}

void	change_position(int key, t_player *player)
{
	const float	coss = cosf(player->pov);
	const float	sinn = sinf(player->pov);

	if (key == KEY_W && check_wall(player, -coss * 8, -sinn * 8))
	{
		player->position_x -= coss * 4;
		player->position_y -= sinn * 4;
	}
	else if (key == KEY_S && check_wall(player, coss * 8, sinn * 8))
	{
		player->position_x += coss * 4;
		player->position_y += sinn * 4;
	}
	else if (key == KEY_D && check_wall(player, sinn * 8, -coss * 8))
	{
		player->position_x += sinn * 4;
		player->position_y -= coss * 4;
	}
	else if (key == KEY_A && check_wall(player, -sinn * 8, coss * 8))
	{
		player->position_x -= sinn * 4;
		player->position_y += coss * 4;
	}
}

void	change_pov(int key, t_player *player)
{
	if (key == KEY_Q)
		player->pov -= PI_DIV_180 * 5;
	else if (key == KEY_E)
		player->pov += PI_DIV_180 * 5;
	if (player->pov >= (2 * PI))
		player->pov -= (float)(2 * PI);
	else if (player->pov <= 0)
		player->pov += (float)(2 * PI);
}

void	counting_player_coordinate(t_player *player, t_map map)
{
	int		count_line;
	int		x;
	int		y;

	y = 0;
	x = 0;
	count_line = 0;
	while (map.map)
	{
		if (ft_strchr(PLAYER_POS, *map.map))
		{
			player_coor_init(player, x, y, *map.map);
			break ;
		}
		if (++count_line == map.length_line)
		{
			y += 64;
			x = 0;
			count_line = 0;
		}
		else
			x += 64;
		map.map++;
	}
}

void	get_wall_texture(t_generic *generic, float ray_angle,
								  float dist_to_wall_h, float dist_to_wall_v)
{
	if (dist_to_wall_h > dist_to_wall_v)
	{
		if ((ray_angle < 2 / PI) || (ray_angle > 3 * PI / 2))
			generic->wall_texture.texture = generic->game_info.textures[0];
		else
			generic->wall_texture.texture = generic->game_info.textures[1];
	}
	else
	{
		if (ray_angle > PI)
			generic->wall_texture.texture = generic->game_info.textures[2];
		else
			generic->wall_texture.texture = generic->game_info.textures[3];
	}
}
