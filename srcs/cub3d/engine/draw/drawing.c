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

void	drawing_celling(t_cub *cub, int wall_y, int wall_x)
{
	const t_img_data	img = cub->screen.img_world;
	const t_color 		celling_color = cub->game_info.celling_color;
	int					index;

	wall_x *= (img.bpp / 8);
	while (wall_y < cub->screen.height)
	{
		index = (wall_y * img.line_length + wall_x);
		if (index > 0)
			put_pixel(img, index, celling_color);
		wall_y++;
	}
}

void	drawing_floor(t_cub *cub, int height, int wall_x)
{
	const t_img_data	img = cub->screen.img_world;
	const t_color		floor_color = cub->game_info.floor_color;
	int					y;
	int					index;

	y = 0;
	wall_x *= (img.bpp / 8);
	while (y < height)
	{
		index = (y * img.line_length + wall_x);
		if (index < cub->screen.height * img.line_length)
			put_pixel(img, index, floor_color);
		y++;
	}
}

void	drawing_wall(t_cub *cub, int wall_y, int height, int wall_x)
{
	const t_img_data	img = cub->screen.img_world;
	t_texture			texture;
	float 				tex_pos;
	int					index;
	int 				index_texture;

	texture = cub->wall_texture;
	texture.step = 1.0f * (float)texture.img_data.height / (float)height;
	texture.x *= (texture.img_data.bpp / 8);
	wall_x *= img.bpp / 8;
	tex_pos = (float)((wall_y - cub->player.look - cub->player.crouch) -
			cub->screen.height / 2 + height / 2) * texture.step;
	while (height-- > 0)
	{
		texture.y = (int)tex_pos & (texture.img_data.height - 1);
		index_texture = texture.y * texture.img_data.line_length + texture.x;
		index = wall_y * img.line_length + wall_x;
		if (index > 0 && index < img.line_length * cub->screen.height)
			put_pixel_img(img, texture.img_data, index, index_texture);
		tex_pos += texture.step;
		wall_y++;
	}
}
