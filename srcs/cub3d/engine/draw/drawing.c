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
	const t_img_data	img_world = map_data->img_world;
	t_wall_texture		texture;
	float 				tex_pos;
	int					index;
	int 				index_texture;

	texture = map_data->wall_texture;
	texture.step = 1.0f * (float)texture.texture.img_height / (float)height;
	texture.x *= (texture.texture.bpp / 8);
	wall_x *= img_world.bpp / 8;
	tex_pos = (wall_y - map_data->resolution[1] / 2 + height / 2) * texture.step;
	while (height-- > 0)
	{
		texture.y = (int)tex_pos & (texture.texture.img_height - 1);
		index_texture = texture.y * texture.texture.line_length + texture.x;
		index = wall_y * img_world.line_length + wall_x;
		if (index > 0 && index < img_world.line_length * map_data->resolution[1])
		{
			img_world.addr[index] = texture.texture.addr[index_texture];
			img_world.addr[index + 1] = texture.texture.addr[index_texture + 1];
			img_world.addr[index + 2] = texture.texture.addr[index_texture + 2];
			img_world.addr[index + 3] = texture.texture.addr[index_texture + 3];
		}
		tex_pos += texture.step;
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
