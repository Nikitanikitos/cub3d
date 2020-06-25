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

void	cast_ray(t_player *player, double corner, int color)
{
	const t_map_data	*map_data = player->map_data;
	const double 		coss = cos(corner * PI / 180);
	const double 		sinn = -sin(corner * PI / 180);
	double				ray_x;
	double				ray_y;
	int					distance_to_wall;

	ray_x = player->position_x;
	ray_y = player->position_y;
	while (map_data->map[(int)ray_x / 64 + (int)ray_y / 64 * map_data->length_line] != '1')
	{
		mlx_pixel_put(player->mlx, player->win, (int)ray_x, (int)ray_y, color);
		ray_x += coss;
		ray_y += sinn;
	}
	distance_to_wall = abs((int)((player->position_x - ray_x) / coss));
	printf("%d\n", distance_to_wall);
}

void	cast_ray_3d(t_player *player, double corner, double wall_x, int color)
{
	const double 		coss = cos(corner * PI / 180);
	double 				sinn = -sin(corner * PI / 180);
	const t_map_data	*map_data = player->map_data;
	double				ray_x;
	double				ray_y;
	double				wall_y;
	double				distance_to_wall;
	double				height;

	ray_x = player->position_x;
	ray_y = player->position_y;
	while (map_data->map[(int)ray_x / 64 + (int)ray_y / 64 * map_data->length_line] != '1')
	{
		ray_x += coss;
		ray_y += sinn;
	}
	distance_to_wall = abs((int)((player->position_x - ray_x) / coss));
//	printf("%f\n", distance_to_wall);
//	distance_to_wall *= coss;
	printf("%f\n", distance_to_wall);
	height = 180 * 40 / distance_to_wall;
	if (player->position_y > ray_y)
		wall_y = map_data->resolution[1] - (player->position_y - ray_y);
	else
		wall_y = map_data->resolution[1] - (ray_y - player->position_y);
	if (sinn < 0)
		sinn = -sinn;
	while (height > 0)
	{
		mlx_pixel_put(player->mlx, player->win, (int)wall_x, (int)wall_y, color);
		height -= sinn;
		wall_y -= sinn;
	}
}

void	field_of_view(t_player *player, int color)
{
	double			corner;
	double			wall_x;
	const double	last_corner = player->pov + ((double)FOV / 2);

	corner = player->pov - ((double)FOV / 2);
	wall_x = player->map_data->resolution[0];
	while (corner != last_corner)
	{
//		cast_ray(player, corner, color);
		cast_ray_3d(player, corner, wall_x, color);
		corner += (double)FOV / PROJECION_PLANE_W;
		wall_x--;
	}
}

int 	print_player(int key, t_player *player)
{
	field_of_view(player, 0);
	change_position(key, player);
	change_pov(key, player);
	field_of_view(player, 225225225);
	return (0);
}

int 	engine(t_map_data *map_data)
{
	t_player	*player;
	void		*mlx;
	void 		*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, map_data->resolution[0], map_data->resolution[1], "Cub3D");
	player = player_init(mlx, win, map_data);
	counting_player_coordinate(map_data->map, player);
//	print_map(win, mlx, map_data->map, player);
	print_player(0, player);
	mlx_key_hook(win, print_player, player);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
