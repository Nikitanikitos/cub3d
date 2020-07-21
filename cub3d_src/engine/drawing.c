/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 01:19:07 by imicah            #+#    #+#             */
/*   Updated: 2020/06/30 01:19:08 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	drawing_floor(t_player *player, short wall_x, float distance_to_wall)
{
	const int	color = player->map_data->floor_color;
	const short	draw_limit = (short)distance_to_wall;
	short		wall_y;

	wall_y = 0;
	while (wall_y < draw_limit)
	{
		mlx_pixel_put(player->mlx, player->win, wall_x, wall_y, color);
		wall_y++;
	}
}

void	drawing_celling(t_player *player, short wall_x, float wall_y)
{
	const int	color = player->map_data->celling_color;
	const int	draw_limit = player->map_data->resolution[1];
	short 		y;

	y = (short)wall_y;
	while (y < draw_limit)
	{
		mlx_pixel_put(player->mlx, player->win, wall_x, y, color);
		y++;
	}
}

//int		get_color_2(t_map_data *map_data, t_player *player, short height)
//{
//	const int 	pixel_ratio = height / 64;
//	t_data		img;
//	int     	img_width;
//	int     	img_height;
//	int 		color;
//	char 		*argb;
//	int 		x;
//	int 		y;
//	int 		coor_x;
//	int 		coor_y;
//	int 		count_x;
//	int 		count_y;
//
//
//	img.img = mlx_xpm_file_to_image(player->mlx, map_data->wall_texture, &img_width, &img_height);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//	y = 0;
//	count_y = 0;
//	coor_y = 0;
//	count_x = pixel_ratio;
//	while (y < 200)
//	{
//		x = 0;
//		coor_x = 0;
//		if (count_y == pixel_ratio)
//		{
//			coor_y++;
//			count_y = 0;
//		}
//		while (x < 200)
//		{
//			if (count_x == pixel_ratio)
//			{
//				argb = img.addr + (coor_y * img.line_length + coor_x * (img.bits_per_pixel / 8));
//				color = get_colorr(argb);
//				count_x = 0;
//				coor_x++;
//			}
//			mlx_pixel_put(player->mlx, player->mlx, x, y, color);
//			x++;
//			count_x++;
//		}
//		y++;
//		count_y++;
//	}
//	sleep(100);
//	return (0);
//}

int		get_colorr(char *line)
{
	int 	color_value;
	int 	pow;
	int 	result;
	int 	q;

	result = 0;
	q = 0;
	pow = 65536;
	while (q < 3)
	{
		color_value = line[q++]; // * 65536
		result += color_value * pow;
		pow /= 256;
	}
	return (result);
}

float	drawing_wall(t_player *player, short wall_x, short wall_y, short height)
{
	const int 	pixel_ratio = height / 64;
	t_data		img;
	int     	img_width;
	int     	img_height;
	int			color;
	static int 	count_x;
	static int 	coor_x;
	int 		count_y;
	int 		coor_y;
	char 		*argb;

	img.img = mlx_xpm_file_to_image(player->mlx, player->map_data->wall_texture, &img_width, &img_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	coor_y = 0;
	count_y = pixel_ratio;
	while (height-- > 0)
	{
		if (count_y == pixel_ratio)
			{
				argb = img.addr + (coor_y * img.line_length + coor_x * (img.bits_per_pixel / 8));
				color = get_colorr(argb);
				count_y = 0;
				coor_y++;
			}
		mlx_pixel_put(player->mlx, player->win, wall_x, wall_y, color);
		wall_y++;
		count_y++;
	}
	count_x++;
	if (count_x == pixel_ratio)
	{
		coor_x++;
		count_x = 0;
	}
	if (coor_x == 64)
		coor_x = 0;
	return (wall_y);
}