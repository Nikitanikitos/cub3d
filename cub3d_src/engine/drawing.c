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

void	drawing_wall_v2(t_map_data *map_data, int wall_x, int wall_y, int height)
{
	const float			pixel_ratio = (float)height / 64;
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
		if (count_y >= pixel_ratio)
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

void	drawing_wall(t_map_data *map_data, int wall_y, int height, int wall_x)
{
	const float			pixel_ratio = (float)height / 64;
	const t_img_data	img = map_data->img_ray;
	const int			x = wall_x * (img.bits_per_pixel / 8);
	const t_img_data	texture = *map_data->texture;
	int					index;
	int 				index_texture;
	int 				coor_y;
	float 				count_y;
	static float 		count_x;
	static int			coor_x;

	coor_y = 0;
	count_y = pixel_ratio;
	wall_y = (wall_y < 0) ? 0 : wall_y;
	height = (height > map_data->resolution[1]) ? map_data->resolution[1] : height;
	while (height-- > 0)
	{
		if (count_y >= pixel_ratio)
		{
			index_texture = coor_y * texture.line_length + coor_x * (texture.bits_per_pixel / 8);
			count_y = 0;
			coor_y++;
		}
		index = (wall_y * img.line_length + x);
		img.addr[index] = texture.addr[index_texture];
		img.addr[index + 1] = texture.addr[index_texture + 1];
		img.addr[index + 2] = texture.addr[index_texture + 2];
		img.addr[index + 3] = 0;
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

void	drawing_floor(t_map_data *map_data, int height, int wall_x)
{
	const t_img_data	img = map_data->img_ray;
	const int 			x = wall_x * (img.bits_per_pixel / 8);
	int					y;
	int					index;

	y = 0;
	while (y < height)
	{
		index = (y * img.line_length + x);
		img.addr[index] = 117;
		img.addr[index + 1] = 187;
		img.addr[index + 2] = 253;
		img.addr[index + 3] = 0;
		y++;
	}
}

void	drawing_celling(t_map_data *map_data, int wall_y, int wall_x)
{
	const t_img_data	img = map_data->img_ray;
	const int			x = wall_x * (img.bits_per_pixel / 8);
	int					index;

	while (wall_y < map_data->resolution[1])
	{
		index = (wall_y * img.line_length + x);
		img.addr[index] = 63;
		img.addr[index + 1] = 155;
		img.addr[index + 2] = 11;
		img.addr[index + 3] = 0;
		wall_y++;
	}
}
