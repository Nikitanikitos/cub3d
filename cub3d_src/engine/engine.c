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

float	distance_to_wall_y(t_player *player, float corner, float sinn)
{
	const t_map_data	*map_data = player->map_data;
	const float			step_y = (sinn > 0) ? -64 : 64;
	const float			step_x = 64 / tanf((float)((corner) * PI_DIVIDED_180));
	float				current_y;
	float				current_x;

	current_y = (int)(player->position_y / 64) * 64;
	current_y += (sinn > 0) ? -1 : 64;
	current_x = player->position_x + (player->position_y - current_y) /
			tanf((float)((corner) * PI_DIVIDED_180));
	while ((int)current_x > 0 && (int)current_x < map_data->resolution[0] &&
			map_data->map[(int)current_x / 64 +
			(int)current_y / 64 * map_data->length_line] != '1')
	{
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrtf(current_x * current_x + current_y * current_y));
}

float	distance_to_wall_x(t_player *player, float corner, float coss)
{
	const t_map_data	*map_data = player->map_data;
	const float			step_x = (coss < 0) ? -64 : 64;
	const float			step_y = 64 * tanf((float)((corner) * PI_DIVIDED_180));
	float				current_y;
	float				current_x;

	current_x = (int)(player->position_x / 64) * 64;
	current_x += (coss > 0) ? 64 : -1;
	current_y = player->position_y + (player->position_x - current_x) *
			tanf((float)((corner) * PI_DIVIDED_180));
	while ((int)current_y > 0 && (int)current_y < map_data->resolution[1] &&
			map_data->map[(int)current_x / 64 +
			(int)current_y / 64 * map_data->length_line] != '1')
	{
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrtf(current_x * current_x + current_y * current_y));
}

void	drawing_floor(t_player *player, short wall_x, short distance_to_wall)
{
	const int	color = player->map_data->floor_color;
	short		wall_y;

	wall_y = 0;
	while (wall_y < distance_to_wall)
	{
		mlx_pixel_put(player->mlx, player->win, wall_x, wall_y, color);
		wall_y++;
	}
}

void	drawing_celling(t_player *player, short wall_x, short wall_y)
{
	const int	color = player->map_data->celling_color;

	while (wall_y < player->map_data->resolution[1])
	{
		mlx_pixel_put(player->mlx, player->win, wall_x, wall_y, color);
		wall_y++;
	}
}

void	cast_ray_3d(t_player *player, float corner, short wall_x)
{
	const t_map_data	*map_data = player->map_data;
	float				distance_to_wall;
	short				height;
	float				distance_x;
	float				distance_y;

	distance_x = distance_to_wall_x(
			player, corner, cosf((float)(corner * PI_DIVIDED_180)));
	distance_y = distance_to_wall_y(
			player, corner, sinf((float)(corner * PI_DIVIDED_180)));
	distance_to_wall = (distance_y < distance_x) ? distance_y : distance_x;
	distance_to_wall *= cosf((float)((player->pov - corner) * PI_DIVIDED_180));
	height = 64 / distance_to_wall *
			((float)map_data->resolution[0] / 2 / tanf(FOV / 2 * PI_DIVIDED_180));
	distance_to_wall = (float)map_data->resolution[1] / 2 - (float)height / 2;
	drawing_floor(player, wall_x, (short)distance_to_wall);
	while (height > 0)
	{
		mlx_pixel_put(player->mlx, player->win,
						wall_x, (int)distance_to_wall, 0x800080);
		distance_to_wall++;
		height--;
	}
	drawing_celling(player, wall_x, (short)distance_to_wall);
}

// угол NW - норм
// угол ES - кривит

void	field_of_view_3d(t_player *player)
{
	const float		step = FOV / (float)player->map_data->resolution[0];
	const float		last_corner = player->pov + (FOV / 2);
	float			corner;
	short			wall_x;

	corner = player->pov - (FOV / 2);
	wall_x = player->map_data->resolution[0];
	while (corner != last_corner)
	{
		cast_ray_3d(player, corner, wall_x);
		corner += step;
		wall_x--;
	}
}

int		game_play(int key, t_player *player)
{
	change_position(key, player);
	change_pov(key, player);
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
//	mlx_expose_hook(win, game_play, player);
	mlx_key_hook(win, game_play, player);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
