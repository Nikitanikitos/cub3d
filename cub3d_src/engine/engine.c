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

double	distance_to_wall_y(t_player *player, double corner, double sinn)
{
	const t_map_data	*map_data = player->map_data;
	const double		step_y = (sinn < 0) ? -64 : 64;
	const double		step_x = 64 / tan((corner) * PI_DIVIDED_180);
	double				current_y;
	double				current_x;

	current_y = (int)(player->position_y / 64) * 64;
	current_y += (sinn < 0) ? -1 : 64;
	current_x = player->position_x + (player->position_y - current_y) /
			tan((corner) * PI_DIVIDED_180);
	while (current_x > 0 && current_x < map_data->resolution[0] &&
			map_data->map[(int)current_x / 64 +
			(int)current_y / 64 * map_data->length_line] != '1')
	{
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrt(current_x * current_x + current_y * current_y));
}

double	distance_to_wall_x(t_player *player, double corner, double coss)
{
	const t_map_data	*map_data = player->map_data;
	const double		step_x = (coss < 0) ? -64 : 64;
	const double		step_y = 64 * tan((corner) * PI_DIVIDED_180);
	double				current_y;
	double				current_x;

	current_x = (int)(player->position_x / 64) * 64;
	current_x += (coss > 0) ? 64 : -1;
	current_y = player->position_y + (player->position_x - current_x) *
			tan((corner) * PI_DIVIDED_180);
	while (current_y > 0 && current_y < map_data->resolution[1] &&
			map_data->map[(int)current_x / 64 +
			(int)current_y / 64 * map_data->length_line] != '1')
	{
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrt(current_x * current_x + current_y * current_y));
}

void	cast_ray_3d(t_player *player, double corner, double wall_x, int color)
{
	const t_map_data	*map_data = player->map_data;
	double				distance_to_wall;
	double				height;
	double				distance_x;
	double				distance_y;

	distance_x = distance_to_wall_x(
			player, corner, cos(corner * PI_DIVIDED_180));
	distance_y = distance_to_wall_y(
			player, corner, -sin(corner * PI_DIVIDED_180));
	distance_to_wall = (distance_y < distance_x) ? distance_y : distance_x;
	distance_to_wall *= cos((player->pov - corner) * PI_DIVIDED_180);
	height = 32 / distance_to_wall *
			(map_data->resolution[0] / 2 / tan((FOV / 2) * PI_DIVIDED_180));
	distance_to_wall = map_data->resolution[1] - distance_to_wall;
	while (height > 0)
	{
		mlx_pixel_put(player->mlx, player->win,
						(int)wall_x, (int)distance_to_wall, color);
		distance_to_wall -= 0.5;
		height -= 0.5;
	}
}

void	field_of_view_3d(t_player *player, int color)
{
	double			corner;
	double			wall_x;
	const double	diff = (double)FOV / player->map_data->resolution[0];
	const double	last_corner = player->pov + ((double)FOV / 2);

	corner = player->pov - ((double)FOV / 2);
	wall_x = player->map_data->resolution[0];
	while (corner != last_corner)
	{
		cast_ray_3d(player, corner, wall_x, color);
		corner += diff;
		wall_x--;
	}
}

int		game_play(int key, t_player *player)
{
	field_of_view_3d(player, 0);
	change_position(key, player);
	change_pov(key, player);
	field_of_view_3d(player, 225225225);
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
//	print_map(win, mlx, map_data->map, player);
//	field_of_view_3d(player, 225225225);
	mlx_key_hook(win, game_play, player);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
