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
	const double 	coss = cos(corner * PI / 180);
	const double 	sinn = -sin(corner * PI / 180);
	double			ray_x;
	double			ray_y;

	ray_x = player->position_x;
	ray_y = player->position_y;
	while (player->map[(int)ray_x / 32 + (int)ray_y / 32 * player->length_line] != '1')
	{
		mlx_pixel_put(player->mlx, player->win, (int)ray_x, (int)ray_y, color);
		ray_x += coss;
		ray_y += sinn;
	}
}

void	field_of_view(t_player *player, int color)
{
	double			corner;
	const double	last_corner = player->pov + ((double)FOV / 2);

	corner = player->pov - ((double)FOV / 2);
	while (corner != last_corner)
	{
		cast_ray(player, corner, color);
		corner += (double)FOV / PROJECION_PLANE_W;
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
	print_player(0, player);
	mlx_key_hook(win, print_player, player);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
