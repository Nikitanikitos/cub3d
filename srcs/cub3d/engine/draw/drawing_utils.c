/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:03:36 by imicah            #+#    #+#             */
/*   Updated: 2020/08/04 15:03:37 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "engine.h"

int		check_transparency(t_img_data texture, int index)
{
	if (texture.addr[index] == 0 && texture.addr[index + 1] == 0 &&
		texture.addr[index + 2] == 0 && texture.addr[index + 3] == 0)
		return (0);
	return (1);
}

float	count_item_dir(t_item item, t_player player, float pov)
{
	float	item_dir;

	item_dir = atan2f(item.y - player.y, item.x - player.x);

	while (item_dir - pov >  M_PI)
		item_dir -= 2 * (float)M_PI;
	while (item_dir - pov < -M_PI)
		item_dir += 2 * (float)M_PI;
	return (item_dir);
}

void	count_offset(t_item *item, t_screen screen, float angle)
{
	const float	fov = 60.f * (float)M_PI / 180;

	item->h_offset = (int)(angle * (float)screen.width / fov +
						   (float)screen.width / 2 - (float)item->height / 2);
	item->v_offset = screen.height / 2 - item->height / 2;
}

void	put_pixel(t_img_data img, int index, t_color color)
{

	img.addr[index] = (char)color.b;
	img.addr[index + 1] = (char)color.g;
	img.addr[index + 2] = (char)color.r;
	img.addr[index + 3] = 0;
}

void	put_pixel_img(t_img_data img, t_img_data texture,
		int index, int index_texture)
{
	img.addr[index] = texture.addr[index_texture];
	img.addr[index + 1] = texture.addr[index_texture + 1];
	img.addr[index + 2] = texture.addr[index_texture + 2];
	img.addr[index + 3] = texture.addr[index_texture + 3];
}