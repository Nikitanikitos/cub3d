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

void	cast_ray_3d(t_map_data *map_data, t_player *player,
					float ray_angle, int wall_x)
{
	float	height;
	float	dist_to_wall;
	float	dist_to_wall_h;
	float	dist_to_wall_v;

	ray_angle += (ray_angle < 0) ? (float)(2 * PI) : 0;
	ray_angle -= (ray_angle > (2 * PI)) ? (float)(2 * PI) : 0;
	dist_to_wall_h = dist_to_wall_horizontal(map_data, player, ray_angle);
	dist_to_wall_v = dist_to_wall_vertical(map_data, player, ray_angle);
	if (dist_to_wall_h > dist_to_wall_v)
		dist_to_wall = dist_to_wall_v * cosf(player->pov - ray_angle);
	else
		dist_to_wall = dist_to_wall_h * cosf(player->pov - ray_angle);
	height = (64 / dist_to_wall * ((float)map_data->resolution[0] /
										2 / tanf(FOV_RAD / 2)));
	dist_to_wall = (float)map_data->resolution[1] / 2 - height / 2;
	get_wall_texture(map_data, ray_angle, dist_to_wall_h, dist_to_wall_v);
	drawing_floor(map_data, (int)dist_to_wall, wall_x);
	drawing_wall(map_data, (int)dist_to_wall, (int)height, wall_x);
	drawing_celling(map_data, (int)(dist_to_wall + height), wall_x);
}

void	field_of_view_3d(t_player *player, t_map_data *map_data)
{
	const float	last_ray_angle = player->pov + (FOV_RAD / 2);
	const float	step = (FOV / (float)map_data->resolution[0]) * PI_DIV_180;
	float		ray_angle;
	int			wall_x;

	ray_angle = player->pov - (FOV_RAD / 2);
	wall_x = 0;
	while (ray_angle <= last_ray_angle)
	{
		cast_ray_3d(map_data, player, ray_angle, wall_x);
		ray_angle += step;
		wall_x++;
	}
	mlx_put_image_to_window(player->mlx, player->win,
							map_data->img_world.img, 0, 0);
}

int		game_play(int key, t_map_data *map_data)
{
	if (key == KEY_E || key == KEY_Q)
		change_pov(key, map_data->player);
	else if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W)
		change_position(key, map_data->player, map_data);
	field_of_view_3d(map_data->player, map_data);
	return (0);
}

int		engine(t_map_data *map_data)
{
	t_img_data	img_world;
	t_player	*player;
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, map_data->resolution[0],
					map_data->resolution[1], "Cub3D");
	img_world.img = mlx_new_image(mlx, map_data->resolution[0],
								map_data->resolution[1]);
	img_world.addr = mlx_get_data_addr(img_world.img, &img_world.bpp,
									&img_world.line_length, &img_world.endian);
	open_texture_files(map_data, mlx);
	player = player_init(mlx, win);
	counting_player_coordinate(map_data->map, player, map_data->length_line);
	map_data->img_world = img_world;
	map_data->player = player;
	player->map = map_data->map;
	field_of_view_3d(player, map_data);
	mlx_hook(win, 2, 1L << 0, game_play, map_data);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
