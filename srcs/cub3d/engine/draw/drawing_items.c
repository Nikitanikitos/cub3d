/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 11:44:57 by imicah            #+#    #+#             */
/*   Updated: 2020/08/05 11:44:58 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

int		check_transparency(t_img_data texture, int index)
{
	if (texture.addr[index] == 0 && texture.addr[index + 1] == 0 &&
		texture.addr[index + 2] == 0 && texture.addr[index + 3] == 0)
		return (0);
	return (1);
}

void	put_item(t_item item, t_screen screen, t_img_data img, int i)
{
	int			j;
	int 		index;
	t_img_data	texture;
	int			index_texture;

	texture = item.texture.img_data;
	j = 0;
	while (j < item.height)
	{
		if (item.v_offset + j > 0 && item.v_offset + j <= screen.height)
		{
			index_texture = j * texture.height / item.height * texture.line_length + i * texture.height / item.height * img.bpp / 8;
			index = (item.v_offset + j) * img.line_length + (item.h_offset + i) * img.bpp / 8;
			if (check_transparency(texture, index_texture))
				put_pixel_img(img, texture, index, index_texture);
		}
		j++;
	}
}

void	drawing_item(t_item item, t_screen screen, float *distances)
{
	const t_img_data	img = screen.img_world;
	int					i;

	i = 0;
	while (i < item.height)
	{
		if ((item.h_offset + i > 0 && item.h_offset + i <= screen.width) &&
			(distances[item.h_offset + i] > item.dist))
			put_item(item, screen, img, i);
		i++;
	}
}

void	sort_items(t_item *items, int number_items)
{
	t_item	temp_item;
	int		q;
	int 	i;
	int		flag;

	q = 0;
	while (q < number_items)
	{
		i = 0;
		flag = 0;
		while (i < number_items - q)
		{
			if (items[i].dist < items[i + 1].dist)
			{
				temp_item = items[i];
				items[i] = items[i + 1];
				items[i + 1] = temp_item;
				flag = 1;
			}
			i++;
		}
		if (flag == 0)
			return;
		q++;
	}
}

void	items_init(t_game_info *game_info, t_player player, t_screen screen)
{
	const float	pov = -player.pov;
	float		sprite_dir;
	t_item		*item;
	int			q;

	q = 0;
	while (q < game_info->number_items)
	{
		item = &game_info->items[q];
		sprite_dir = count_item_dir(*item, player, pov);
		item->dist = get_distance(player.x - item->x, player.y - item->y);
		item->height = (int)count_height(item->dist, screen);
		item->texture.img_data = game_info->sprite_texture;
		count_offset(item, screen, sprite_dir - pov);
		q++;
	}
}

void	drawing_items(t_game_info game_info, t_player player, t_screen screen, float *distances)
{
	int 		q;
	t_item		item;

	q = 0;
	items_init(&game_info, player, screen);
	sort_items(game_info.items, game_info.number_items);
	while (q < game_info.number_items)
	{
		item = game_info.items[q];
		drawing_item(item, screen, distances);
		q++;
	}
}
