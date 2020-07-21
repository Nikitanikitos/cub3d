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

float	dist_to_wall_horizontal(t_map_data *map_data, t_player *player, float ray_angle)
{
	const float			step_y = (ray_angle < PI) ? -64 : 64;
	const float			step_x = -step_y * (-1 / tanf(ray_angle));
	float				current_y;
	float				current_x;

	current_y = (float)((int)(player->position_y / 64) * 64);
	current_y += (ray_angle < PI) ? -.01f : 64;
	current_x = player->position_x + (player->position_y - current_y) *
									 (-1 / tanf(ray_angle));
	while ((int)current_x > 0 && (int)current_y > 0 &&
		   (int)current_y < map_data->resolution[1] && (int)current_x < map_data->resolution[0])
	{
		if (map_data->map[(int)(current_x / 64) + (int)(current_y / 64) *
												  map_data->length_line] == '1')
			break ;
		current_x += step_x;
		current_y += step_y;
	}
	current_x = player->position_x - current_x;
	current_y = player->position_y - current_y;
	return (sqrtf(current_x * current_x + current_y * current_y));
}

float	dist_to_wall_vertical(t_map_data *map_data, t_player *player, float ray_angle)
{
	const float			step_x = (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? -64 : 64;
	const float			step_y = -step_x * -tanf(ray_angle);
	float				current_y;
	float				current_x;

	current_x = (float)((int)(player->position_x / 64) * 64);
	current_x += (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2)) ? -.01f : 64;
	current_y = player->position_y + (player->position_x - current_x) *
									 -tanf(ray_angle);
	while ((int)current_x > 0 && (int)current_y > 0 &&
		   (int)current_y < map_data->resolution[1] && (int)current_x < map_data->resolution[0])
	{
		if (map_data->map[(int)(current_x / 64) + (int)(current_y / 64) *
												  map_data->length_line] == '1')
			break ;
		current_x += step_x;
		current_y += step_y;
	}
	current_x = (player->position_x - current_x);
	current_y = (player->position_y - current_y);
	return (sqrtf(current_x * current_x + current_y * current_y));
}

char		*get_wall_color(const t_map_data *map_data, float ray_angle,
							float dist_to_wall_h, float dist_to_wall_v)
{
	if (dist_to_wall_h > dist_to_wall_v)
	{
		if ((ray_angle < 2 / PI) || (ray_angle > 3 * PI / 2))
			return (map_data->textures[0]);
		else
			return (map_data->textures[1]);
	}
	else
	{
		if (ray_angle > PI)
			return (map_data->textures[2]);
		else
			return (map_data->textures[3]);
	}
}

void	cast_ray_3d(t_map_data *map_data, t_player *player, float ray_angle, int wall_x)
{
	int			height;
	float		dist_to_wall;
	float		dist_to_wall_h;
	float		dist_to_wall_v;

	if (ray_angle < 0)
		ray_angle += (float)(2 * PI);
	else if (ray_angle > (2 * PI))
		ray_angle -= (float)(2 * PI);

	dist_to_wall_h = dist_to_wall_horizontal(map_data, player, ray_angle);
	dist_to_wall_v = dist_to_wall_vertical(map_data, player, ray_angle);

	if (dist_to_wall_h > dist_to_wall_v)
		dist_to_wall = dist_to_wall_v * cosf(player->pov - ray_angle);
	else
		dist_to_wall = dist_to_wall_h * cosf(player->pov - ray_angle);

	height = (int)(64 / dist_to_wall * ((float)map_data->resolution[0] /
														2 / tanf(FOV_RAD / 2)));
	dist_to_wall = (float)map_data->resolution[1] / 2 - (float)height / 2;

//	map_data->wall_texture = get_wall_color(map_data, ray_angle, dist_to_wall_h, dist_to_wall_v);
	drawing_floor(player, wall_x, dist_to_wall);
	dist_to_wall = drawing_wall(player, wall_x, (int)dist_to_wall, height);
	drawing_celling(player, wall_x, dist_to_wall);
}

void	field_of_view_3d(t_player *player, t_map_data *map_data)
{
	const float	last_ray_angle = player->pov + (FOV_RAD / 2);
	float		step;
	float		ray_angle;
	int			wall_x;

	step = (FOV / (float)map_data->resolution[0]) * PI_DIVIDED_180;
	ray_angle = player->pov - (FOV_RAD / 2);
	wall_x = 0;
	while (ray_angle <= last_ray_angle)
	{
		cast_ray_3d(map_data, player, ray_angle, wall_x);
		ray_angle += step;
		wall_x++;
	}
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

void	open_texture_files(t_map_data *map_data, void *mlx)
{
	t_texture_data	*img;
	int 			q;

	q = 0;
	while (q < 4)
	{
		img = (t_texture_data*)malloc(sizeof(t_texture_data));
		map_data->textures_img[q] = img;
		img->img = mlx_xpm_file_to_image(mlx, map_data->textures[q], &img->img_width, &img->img_height);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
		q++;
	}
}

int		engine(t_map_data *map_data)
{
	t_player	*player;
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	open_texture_files(map_data, mlx);
	win = mlx_new_window(
			mlx, map_data->resolution[0], map_data->resolution[1], "Cub3D");
	player = player_init(mlx, win);
	map_data->player = player;
	player->map = map_data->map;
	counting_player_coordinate(player->map, player, map_data->length_line);
	field_of_view_3d(player, map_data);
	mlx_hook(win, 2, 1L << 0, game_play, map_data);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
