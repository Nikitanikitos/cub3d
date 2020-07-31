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
	const int	coor_x = (int)((player->x + step_x) / 64);
	const int	coor_y = (int)((player->y + step_y) / 64);
	t_map		map = player->map;

	return (char)(map.map[coor_x + coor_y * map.length_line] != '1');
}

void	change_position(int key, t_player *player)
{
	const float	coss = cosf(player->pov);
	const float	sinn = -sinf(player->pov);

	if (key == KEY_W && check_wall(player, coss * 8, sinn * 8))
	{
		player->x += coss * 4;
		player->y += sinn * 4;
	}
	else if (key == KEY_S && check_wall(player, -coss * 8, -sinn * 8))
	{
		player->x -= coss * 4;
		player->y -= sinn * 4;
	}
	else if (key == KEY_D && check_wall(player, -sinn * 8, coss * 8))
	{
		player->x -= sinn * 4;
		player->y += coss * 4;
	}
	else if (key == KEY_A && check_wall(player, sinn * 8, -coss * 8))
	{
		player->x += sinn * 4;
		player->y -= coss * 4;
	}
}

void	change_pov(int key, t_player *player)
{
	if (key == KEY_Q)
		player->pov += PI_DIV_180 * 5;
	else if (key == KEY_E)
		player->pov -= PI_DIV_180 * 5;
	if (player->pov >= (2 * PI))
		player->pov -= (float)(2 * PI);
	else if (player->pov <= 0)
		player->pov += (float)(2 * PI);
}

void	get_wall_texture(t_cub *cub, float ray_angle,
						 float dist_to_wall_h, float dist_to_wall_v)
{
	if (dist_to_wall_h > dist_to_wall_v)
	{
		if ((ray_angle < 2 / PI) || (ray_angle > 3 * PI / 2))
			cub->wall_texture.texture = cub->game_info.textures[0];
		else
			cub->wall_texture.texture = cub->game_info.textures[1];
	}
	else
	{
		if (ray_angle > PI)
			cub->wall_texture.texture = cub->game_info.textures[2];
		else
			cub->wall_texture.texture = cub->game_info.textures[3];
	}
}
