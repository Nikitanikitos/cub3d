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

void	drawing_floor(t_player *player, int wall_x, int draw_limit, int color)
{
	int		wall_y;

	wall_y = 0;
	while (wall_y < draw_limit)
		mlx_pixel_put(player->mlx, player->win, wall_x, wall_y++, color);
}

void	drawing_celling(t_map_data *map_data, int wall_x, int wall_y, int color)
{
	const int	draw_limit = map_data->resolution[1];

	while (wall_y < draw_limit)
		mlx_pixel_put(map_data->player->mlx, map_data->player->win, wall_x, wall_y++, color);
}

void	drawing_wall(t_map_data *map_data, int wall_x, int wall_y, int height)
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

void	drawing_wall_v2(t_map_data *map_data, int wall_y, int height, int wall_x)
{
	const t_img_data	img = map_data->img_ray;
	const int			x = wall_x * (img.bits_per_pixel / 8);
	int					index;

	if (wall_y < 0)
		wall_y = 0;
	if (height > map_data->resolution[1])
		height = map_data->resolution[1];
	while (height-- > 0)
	{
		index = (wall_y * img.line_length + x);
		img.addr[index] = 80;
		img.addr[index + 1] = 80;
		img.addr[index + 2] = 80;
		img.addr[index + 3] = 0;
		wall_y++;
	}
}

void	drawing_floor_v3(t_map_data *map_data, int height, int wall_x)
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

void	drawing_celling_v3(t_map_data *map_data, int wall_y, int wall_x)
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
