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

float	count_item_dir(t_item item, t_player player, float pov)
{
	float	item_dir;

	item_dir = atan2f(item.y - player.y, item.x - player.x);

	while (item_dir - pov >  M_PI)
		item_dir -= 2 * M_PI;
	while (item_dir - pov < -M_PI)
		item_dir += 2 * M_PI;
	return (item_dir);
}

void	count_offset(t_item *item, t_screen screen, float angle)
{
	const float	fov = 60 * M_PI / 180;

	item->h_offset = (int)(angle * (float)screen.width / fov +
						   (float)screen.width / 2 - (float)item->height / 2);
	item->v_offset = screen.height / 2 - item->height / 2;
}