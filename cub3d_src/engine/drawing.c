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

void	drawing_wall(t_map_data *map_data, int wall_y, int height, int wall_x)
{
	const float			pixel_ratio = (float)height / 64;
	const t_img_data	img_world = map_data->img_world;
	const t_img_data	texture = map_data->texture;
	int					index;
	int 				index_texture;
	int 				coor_y;
	float 				count_y;
	static float 		count_x;
	static int			coor_x;

	coor_y = 0;
	count_y = pixel_ratio;
	wall_y = (wall_y < 0) ? 0 : wall_y;
	wall_x *= img_world.bpp / 8;
	height = (height > map_data->resolution[1]) ? map_data->resolution[1] : height;
	while (height-- > 0)
	{
		if (count_y >= pixel_ratio)
		{
			index_texture = coor_y * texture.line_length + coor_x * (texture.bpp / 8);
			count_y = 0;
			coor_y++;
		}
		index = (wall_y * img_world.line_length + wall_x);
		img_world.addr[index] = texture.addr[index_texture];
		img_world.addr[index + 1] = texture.addr[index_texture + 1];
		img_world.addr[index + 2] = texture.addr[index_texture + 2];
		img_world.addr[index + 3] = texture.addr[index_texture + 3];
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

void	drawing_wall_v2(t_map_data *map_data, int wall_y, int height, int wall_x, float x)
{
	const t_img_data	img_world = map_data->img_world;
	const t_img_data	texture = map_data->texture;
	const float 		step = 1.0f * (float)texture.img_height / (float)height;
	const int 			coor_x = (int)(64 * x);
	float 				tex_pos;
	int					index;
	int 				index_texture;
	int 				coor_y;

	wall_x *= img_world.bpp / 8;
	tex_pos = (float)(wall_y - map_data->resolution[1] / 2 + height / 2) * step;
	while (height-- > 0)
	{
		coor_y = (int)tex_pos & (texture.img_height - 1);
		index_texture = coor_y * texture.line_length + coor_x * (texture.bpp / 8);
		index = (wall_y * img_world.line_length + wall_x);
		if (index > 0 && index < img_world.line_length * map_data->resolution[1])
		{
			img_world.addr[index] = texture.addr[index_texture];
			img_world.addr[index + 1] = texture.addr[index_texture + 1];
			img_world.addr[index + 2] = texture.addr[index_texture + 2];
			img_world.addr[index + 3] = texture.addr[index_texture + 3];
		}
		tex_pos += step;
		wall_y++;
	}
}


void	drawing_floor(t_map_data *map_data, int height, int wall_x)
{
	const t_img_data	img = map_data->img_world;
	int					y;
	int					index;

	y = 0;
	wall_x *= (img.bpp / 8);
	while (y < height)
	{
		index = (y * img.line_length + wall_x);
		img.addr[index] = 0;
		img.addr[index + 1] = map_data->floor_color[0];
		img.addr[index + 2] = map_data->floor_color[1];
		img.addr[index + 3] = map_data->floor_color[2];
		y++;
	}
}

void	drawing_celling(t_map_data *map_data, int wall_y, int wall_x)
{
	const t_img_data	img = map_data->img_world;
	int					index;

	wall_x *= (img.bpp / 8);
	while (wall_y < map_data->resolution[1])
	{
		index = (wall_y * img.line_length + wall_x);
		img.addr[index] = 0;
		img.addr[index + 1] = map_data->celling_color[0];
		img.addr[index + 2] = map_data->celling_color[1];
		img.addr[index + 3] = map_data->celling_color[2];
		wall_y++;
	}
}
