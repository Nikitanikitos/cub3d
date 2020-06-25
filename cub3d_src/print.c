/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:39:12 by imicah            #+#    #+#             */
/*   Updated: 2020/06/25 16:39:13 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"


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
