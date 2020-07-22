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

void	drawing_floor(t_player *player, int wall_x, int draw_limit, int color)
{
	int		wall_y;

	wall_y = 0;
	while (wall_y < draw_limit)
		mlx_pixel_put(player->mlx, player->win, wall_x, wall_y++, color);
}

void	drawing_celling(t_map_data *map_data, int wall_x, int wall_y, int color)
{
	const int	draw_limit = map_data->resolution[1];

	while (wall_y < draw_limit)
		mlx_pixel_put(map_data->player->mlx, map_data->player->win, wall_x, wall_y++, color);
}

void	drawing_floor_v2(t_map_data *map_data)
{
	t_img_data	img;
	int			y;
	const int	height = map_data->resolution[1] / 2;;
	int 		x;
	int 		index;

	y = 0;
	img.img = mlx_new_image(map_data->player->mlx, map_data->resolution[0], height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (y < height)
	{
		x = 0;
		while (x < img.line_length)
		{
			index = (y * img.line_length + x * (img.bits_per_pixel / 8));
			img.addr[index] = 117;
			img.addr[index + 1] = 187;
			img.addr[index + 2] = 253;
			img.addr[index + 3] = 0;
			x += 1;
		}
		y++;
	}
	mlx_put_image_to_window(map_data->player->mlx, map_data->player->win, img.img, 0, 0);
}

void	drawing_celling_v2(t_map_data *map_data)
{
	t_img_data	img;
	int			y;
	const int	height = map_data->resolution[1] / 2;;
	int 		x;
	int 		index;

	y = 0;
	img.img = mlx_new_image(map_data->player->mlx, map_data->resolution[0], height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	while (y < height)
	{
		x = 0;
		while (x < img.line_length)
		{
			index = (y * img.line_length + x * (img.bits_per_pixel / 8));
			img.addr[index] = 63;
			img.addr[index + 1] = 155;
			img.addr[index + 2] = 11;
			img.addr[index + 3] = 0;
			x += 1;
		}
		y++;
	}
	mlx_put_image_to_window(map_data->player->mlx, map_data->player->win, img.img, 0, height);
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

void	drawing_wall(t_map_data *map_data, int wall_x, int wall_y, int height)
{
	const float			pixel_ratio = roundf((float)height / 64);
	const t_img_data	img = *map_data->texture;
	static float 		count_x;
	static int 			coor_x;
	float 				count_y;
	char 				*argb;
	int					color;
	int 				coor_y;

	coor_y = 0;
	count_y = pixel_ratio;
	while (height-- > 0)
	{
		if (count_y == pixel_ratio)
			{
				argb = img.addr + (coor_y * img.line_length + coor_x * (img.bits_per_pixel / 8)) + 1;
				color = get_colorr(argb);
				count_y = 0;
				coor_y++;
			}
		mlx_pixel_put(map_data->player->mlx, map_data->player->win, wall_x, wall_y, color);
		wall_y++;
		count_y++;
	}
	count_x++;
	if (count_x >= pixel_ratio)
	{
		coor_x++;
		count_x = 0;
	}
	if (coor_x == 64)
		coor_x = 0;
}
