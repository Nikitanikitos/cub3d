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

void	drawing_wall(t_cub *cub, int wall_y, int height, int wall_x)
{
	const t_img_data	img = cub->screen.img_world;
	t_texture			texture;
	float 				tex_pos;
	int					index;
	int 				index_texture;

	texture = cub->wall_texture;
	texture.step = 1.0f * (float)texture.texture.img_height / (float)height;
	texture.x *= (texture.texture.bpp / 8);
	wall_x *= img.bpp / 8;
	tex_pos = (wall_y - cub->screen.height / 2 + height / 2) * texture.step;
	while (height-- > 0)
	{
		texture.y = (int)tex_pos & (texture.texture.img_height - 1);
		index_texture = texture.y * texture.texture.line_length + texture.x;
		index = wall_y * img.line_length + wall_x;
		if (index > 0 && index < img.line_length * cub->screen.height)
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
		img.addr[index] = (char)floor_color.b;
		img.addr[index + 1] = (char)floor_color.g;
		img.addr[index + 2] = (char)floor_color.r;
		img.addr[index + 3] = 0;
		y++;
	}
}

void	drawing_celling(t_cub *cub, int wall_y, int wall_x)
{
	const t_img_data	img = cub->screen.img_world;
	const t_color 		celling_color = cub->game_info.celling_color;
	int					index;

	wall_x *= (img.bpp / 8);
	while (wall_y < cub->screen.height)
	{
		index = (wall_y * img.line_length + wall_x);
		img.addr[index] = (char)celling_color.b;
		img.addr[index + 1] = (char)celling_color.g;
		img.addr[index + 2] = (char)celling_color.r;
		img.addr[index + 3] = 0;
		wall_y++;
	}
}

void	put_item_col(t_item item, t_screen screen, t_img_data img, int i)
{
	int			j;
	int 		index;
	t_img_data	texture;
	int			index_texture;

	texture = item.texture.texture;
	j = 0;
	while (j < item.height)
	{
		if (item.v_offset + j > 0 && item.v_offset + j <= screen.height)
		{
			index_texture = j * texture.img_height/item.height * texture.line_length + i * texture.img_height/item.height * img.bpp / 8;
			index = (item.v_offset + j) * img.line_length + (item.h_offset + i) * img.bpp / 8;
			img.addr[index] = texture.addr[index_texture];
			img.addr[index + 1] = texture.addr[index_texture + 1];
			img.addr[index + 2] = texture.addr[index_texture + 2];
			img.addr[index + 3] = texture.addr[index_texture + 3];
		}
		j++;
	}
}

void	put_item(t_item item, t_screen screen, float *distances)
{
	const t_img_data	img = screen.img_world;
	int					i;

	i = 0;
	while (i < item.height)
	{
		if ((item.h_offset + i > 0 && item.h_offset + i <= screen.width) &&
			(distances[item.h_offset + i] > item.dist))
			put_item_col(item, screen, img, i);
		i++;
	}
}

void	drawing_items(t_game_info game_info, t_player player, t_screen screen, float *distances)
{
	const float	pov = -player.pov;
	float		sprite_dir;
	t_item		item;
	int			q;

	q = 0;
	while (q < game_info.map.count_item)
	{
		item = game_info.items[q];
		sprite_dir = count_item_dir(item, player, pov);
		item.dist = get_distance(player.x - item.x, player.y - item.y);
		item.height = (int)count_height(item.dist, screen);
		item.texture.texture = game_info.sprite_texture;
		count_offset(&item, screen, sprite_dir - pov);
		put_item(item, screen, distances);
		q++;
	}
}
