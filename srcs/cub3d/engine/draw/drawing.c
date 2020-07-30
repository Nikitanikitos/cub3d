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

void	drawing_items(t_game_info game_info, t_player player, t_screen screen)
{
	int		q;
	float	sprite_dir;
	float	sprite_dist;
	float	height;
	int		h_offset;
	int		v_offset;

	q = 0;
	while (q <= game_info.map.count_item)
	{
		sprite_dir = atan2f(player.position_y - game_info.items[q].y, player.position_x - game_info.items[q].x);
		sprite_dist = get_distance(player.position_x - game_info.items[q].x, player.position_y - game_info.items[q].y);
		height = count_height_wall(sprite_dist, screen);
		h_offset = (int)((sprite_dir - player.pov) * (float)screen.width / FOV + (float)screen.width / 2 - height / 2);
		v_offset = (int)((float)screen.height / 2 - height / 2);
		q++;
		for (size_t i = 0; i < height; i++)
		{
			if (h_offset + i < 0 || h_offset+i>=screen.width/2)
				continue;
			for (size_t j = 0; j<height; j++)
			{
				if (v_offset + j < 0 || v_offset+j>=screen.width)
					continue;
				mlx_pixel_put(screen.mlx, screen.win, screen.width + h_offset+i, v_offset+j, 0000);
			}
		}
	}
}