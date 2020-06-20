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
#include <stdio.h>
#define FOV 60
#define POV 277

int 	print_player(int key, t_player *player);

void print_wall(void *win, t_xvar *mlx, unsigned short pos_x, unsigned short pos_y)
{
	unsigned short  x;
	unsigned short  y;

	x = 0;
	y = 0;
	while (x <= 32)
	{
		while (y <= 32)
			mlx_pixel_put(mlx,win, pos_x + x, pos_y + y++,02550);
		x++;
		y = 0;
	}
}

void	cast_ray(void *mlx, void *win, t_player *player, int color)
{
	int 	ray_x;
	int		ray_y;
	int 	x;
	int 	y;
	int		mod_x;
	int		mod_y;

	ray_x = player->position_x;
	ray_y = player->position_y;
	mod_x = ray_x % 32;
	mod_y = ray_y % 32;
	y = x = 0;
	while (player->map[(ray_x / 32 + player->direction_x) +
				(ray_y / 32 + player->direction_y) * player->length_line] != '1')
	{
		while (-32 <= y && y <= 32 && -32 <= x && x <= 32)
		{
			mlx_pixel_put(mlx, win, ray_x + x, ray_y + y,color);
			y += player->direction_y;
			x += player->direction_x;
		}
		ray_x += 32 * player->direction_x;
		ray_y += 32 * player->direction_y;
		y = x = 0;
	}
	while (-mod_y < y && y < (32 - mod_y) && -mod_x < x && x < (32 - mod_x))
	{
		mlx_pixel_put(mlx, win, ray_x + x, ray_y + y,color);
		y += player->direction_y;
		x += player->direction_x;
	}
}

int 	print_player(int key, t_player *player)
{
	cast_ray(player->mlx, player->win, player, 0);
	if (key == KEY_W)
		player->position_y -= 4;
	else if (key == KEY_S)
		player->position_y += 4;
	else if (key == KEY_D)
		player->position_x += 4;
	else if (key == KEY_A)
		player->position_x -= 4;
	cast_ray(player->mlx, player->win, player, 225225225);
	return (0);
}

void 	print_map(void *win, t_xvar *mlx, char *map, t_player *player)
{
	char 			count_line;
	unsigned short	x;
	unsigned short	y;

	y = 0;
	x = 0;
	count_line = 0;
	while (*map)
	{
		if (*map == '1')
			print_wall(win, mlx, x, y);
		else if (ft_strchr(PLAYER_POS, *map))
			player_coor_init(player, x, y, *map);
		if (++count_line == player->length_line)
		{
			y += 32;
			x = 0;
			count_line = 0;
		}
		else
			x += 32;
		map++;
	}
}

int 	engine(t_map_data *map_data)
{
	t_player	*player;
	void		*mlx;
	void 		*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, map_data->resolution[0], map_data->resolution[1], "Cub3D");
	player = player_init(mlx, win, map_data);
	print_map(win, mlx, map_data->map, player);
	print_player(0, player);
	mlx_key_hook(win, print_player, player);
	mlx_loop(mlx);
	free_player(player);
	return (0);
}
