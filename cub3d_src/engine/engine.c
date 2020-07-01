/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 15:59:41 by imicah            #+#    #+#             */
/*   Updated: 2020/06/16 15:59:42 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"

float	distance_to_wall_y(t_player *player, float corner)
{
	const t_map_data	*map_data = player->map_data;
	const float			step_y = (corner < PI && corner > 0) ? -64 : 64;
	const float			step_x = 64 / tanf(corner);
	float				current_y;
	float				current_x;

	current_y = (int)(player->position_y / 64) * 64;
	current_y += (corner < PI && corner > 0) ? -1 : 64;
	current_x = player->position_x + (player->position_y - current_y) /
																tanf(corner);
	while ((int)current_x >= 0 && (int)current_x <= map_data->resolution[0])
	{
		if (map_data->map[(int)current_x / 64 + (int)current_y / 64 *
												map_data->length_line] == '1')
			break ;
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrtf(current_x * current_x + current_y * current_y));
}

float	distance_to_wall_x(t_player *player, float corner)
{
	const t_map_data	*map_data = player->map_data;
	const float			step_x = (corner < (PI / 2) || corner > (3 * PI / 2)) ? 64 : -64;
	const float			step_y = 64 * tanf(corner);
	float				current_y;
	float				current_x;

	current_x = (int)(player->position_x / 64) * 64;
	current_x += (corner < (PI / 2) || corner > (3 * PI / 2)) ? 64 : -1;
	current_y = player->position_y + (player->position_x - current_x) *
																tanf(corner);
	while ((int)current_y >= 0 && (int)current_y <= map_data->resolution[1])
	{
		if (map_data->map[(int)current_x / 64 + (int)current_y / 64 *
												map_data->length_line] == '1')
			break ;
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrtf(current_x * current_x + current_y * current_y));
}

void	cast_ray_3d(t_player *player, float corner, short wall_x)
{
	const t_map_data	*map_data = player->map_data;
	float				distance_to_wall;
	short				height;
	float				distance_x;
	float				distance_y;

	if (corner < 0)
		corner += (float)(2.f * PI);
	else if (corner > (2.f * PI))
		corner -= (float)(2.f * PI);
	distance_x = distance_to_wall_x(player, corner);
	distance_y = distance_to_wall_y(player, corner);
	distance_to_wall = (distance_y < distance_x) ? distance_y : distance_x;
	distance_to_wall *= cosf(player->pov - corner);
	height = (short)(64 / distance_to_wall * ((float)map_data->resolution[0] /
														2 / tanf(FOV_RAD / 2)));
	distance_to_wall = (float)map_data->resolution[1] / 2 - (float)height / 2;
	drawing_floor(player, wall_x, distance_to_wall);
	distance_to_wall = drawing_wall(player, wall_x, distance_to_wall, height);
	drawing_celling(player, wall_x, distance_to_wall);
}

// угол NW - норм
// угол ES - кривит

void	field_of_view_3d(t_player *player)
{
	const float		last_corner = player->pov + (FOV_RAD / 2);
	float			step;
	float			corner;
	short			wall_x;

	step = (FOV / (float)player->map_data->resolution[0]) * PI_DIVIDED_180;
	corner = player->pov - (FOV_RAD / 2);
	wall_x = player->map_data->resolution[0];
	while (corner <= last_corner)
	{
		cast_ray_3d(player, corner, wall_x);
		corner += step;
		wall_x--;
	}
}

int		game_play(int key, t_player *player)
{
	if (key == KEY_E || key == KEY_Q)
		change_pov(key, player);
	else if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W)
		change_position(key, player);
	field_of_view_3d(player);
	return (0);
}

int		engine(t_map_data *map_data)
{
	t_player	*player;
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	win = mlx_new_window(
			mlx, map_data->resolution[0], map_data->resolution[1], "Cub3D");
	player = player_init(mlx, win, map_data);
	counting_player_coordinate(map_data->map, player);
	field_of_view_3d(player);
	mlx_key_hook(win, game_play, player);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
