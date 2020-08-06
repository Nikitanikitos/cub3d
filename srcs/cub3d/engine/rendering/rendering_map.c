/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 20:08:20 by imicah            #+#    #+#             */
/*   Updated: 2020/06/25 20:08:21 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void print_wall(void *win, t_xvar *mlx, unsigned short pos_x, unsigned short pos_y)
{
	unsigned short  x;
	unsigned short  y;

	x = 0;
	y = 0;
	while (x <= 64)
	{
		while (y <= 64)
			mlx_pixel_put(mlx,win, pos_x + x, pos_y + y++,02550);
		x++;
		y = 0;
	}
}

//void 	print_map(void *win, t_xvar *mlx, char *map, t_player *player)
//{
//	char 			count_line;
//	unsigned short	x;
//	unsigned short	y;
//
//	y = 0;
//	x = 0;
//	count_line = 0;
//	while (*map)
//	{
//		if (*map == '1')
//			print_wall(win, mlx, x, y);
//		else if (ft_strchr(PLAYER_POS, *map))
//			player_coor_init(player, x, y, *map);
//		if (++count_line == player->map_data->line_length)
//		{
//			y += 64;
//			x = 0;
//			count_line = 0;
//		}
//		else
//			x += 64;
//		map++;
//	}
//}

//void	ray_casting(t_player *player, double corner, int color)
//{
//	const t_map_data	*map_data = player->map_data;
//	const double 		coss = cos(corner * PI / 180);
//	const double 		sinn = -sin(corner * PI / 180);
//	double				ray_x;
//	double				ray_y;
//
//	ray_x = player->position_x;
//	ray_y = player->position_y;
//	while (map_data->map[(int)ray_x / 64 + (int)ray_y / 64 * map_data->line_length] != '1')
//	{
//		mlx_pixel_put(player->mlx, player->win, (int)ray_x, (int)ray_y, color);
//		ray_x += coss;
//		ray_y += sinn;
//	}
//}

//void	frame_rendering(t_player *player, int color)
//{
//	double			corner;
//	const double	diff = (double)FOV / player->map_data->resolution[0];
//	const double	last_corner = player->pov + ((double)FOV / 2);
//
//	corner = player->pov - ((double)FOV / 2);
//	while (corner != last_corner)
//	{
//		ray_casting(player, corner, color);
//		corner += diff;
//	}
//}