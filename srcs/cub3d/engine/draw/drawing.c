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

void	drawing_wall(t_generic *generic, int wall_y, int height, int wall_x)
{
	const t_img_data	img = generic->screen.img_world;
	t_wall_texture		texture;
	float 				tex_pos;
	int					index;
	int 				index_texture;

	texture = generic->wall_texture;
	texture.step = 1.0f * (float)texture.texture.img_height / (float)height;
	texture.x *= (texture.texture.bpp / 8);
	wall_x *= img.bpp / 8;
	tex_pos = (wall_y - generic->screen.resolution[1] / 2 + height / 2) * texture.step;
	while (height-- > 0)
	{
		texture.y = (int)tex_pos & (texture.texture.img_height - 1);
		index_texture = texture.y * texture.texture.line_length + texture.x;
		index = wall_y * img.line_length + wall_x;
		if (index > 0 && index < img.line_length * generic->screen.resolution[1])
		{
			img.addr[index] = texture.texture.addr[index_texture];
			img.addr[index + 1] = texture.texture.addr[index_texture + 1];
			img.addr[index + 2] = texture.texture.addr[index_texture + 2];
			img.addr[index + 3] = texture.texture.addr[index_texture + 3];
		}
		tex_pos += texture.step;
		wall_y++;
	}
}

void	drawing_floor(t_generic *generic, int height, int wall_x)
{
	const t_img_data	img = generic->screen.img_world;
	const t_color		floor_color = generic->game_info.floor_color;
	int					y;
	int					index;

	y = 0;
	wall_x *= (img.bpp / 8);
	while (y < height)
	{
		index = (y * img.line_length + wall_x);
		img.addr[index] = (char)floor_color.b;
		img.addr[index + 1] = (char)floor_color.g;
		img.addr[index + 2] = (char)floor_color.r;
		img.addr[index + 3] = 0;
		y++;
	}
}

void	drawing_celling(t_generic *generic, int wall_y, int wall_x)
{
	const t_img_data	img = generic->screen.img_world;
	const t_color 		celling_color = generic->game_info.celling_color;
	int					index;

	wall_x *= (img.bpp / 8);
	while (wall_y < generic->screen.resolution[1])
	{
		index = (wall_y * img.line_length + wall_x);
		img.addr[index] = (char)celling_color.b;
		img.addr[index + 1] = (char)celling_color.g;
		img.addr[index + 2] = (char)celling_color.r;
		img.addr[index + 3] = 0;
		wall_y++;
	}
}
