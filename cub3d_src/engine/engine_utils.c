/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:42:02 by imicah            #+#    #+#             */
/*   Updated: 2020/06/25 16:42:03 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

char		check_wall(t_player *player, float step_x, float step_y, int length_line)
{
	char		*map = player->map;
	const int	coor_x = (int)((player->position_x + step_x) / 64);
	const int	coor_y = (int)((player->position_y + step_y) / 64);

	if (map[coor_x + coor_y * length_line] != '1')
		return (1);
	return (0);
}

void		change_position(int key, t_player *player, t_map_data *map_data)
{
	const float	coss = cosf(player->pov);
	const float	sinn = sinf(player->pov);
	const int	length_line = map_data->length_line;

	if (key == KEY_W && check_wall(player, -coss * 8, -sinn * 8, length_line))
	{
		player->position_x -= coss * 4;
		player->position_y -= sinn * 4;
	}
	else if (key == KEY_S && check_wall(player, coss * 8, sinn * 8, length_line))
	{
		player->position_x += coss * 4;
		player->position_y += sinn * 4;
	}
	else if (key == KEY_D && check_wall(player, sinn * 8, -coss * 8, length_line))
	{
		player->position_x += sinn * 4;
		player->position_y -= coss * 4;
	}
	else if (key == KEY_A && check_wall(player, -sinn * 8, coss * 8, length_line))
	{
		player->position_x -= sinn * 4;
		player->position_y += coss * 4;
	}
}

void		change_pov(int key, t_player *player)
{
	if (key == KEY_Q)
		player->pov -= PI_DIVIDED_180 * 5;
	else if (key == KEY_E)
		player->pov += PI_DIVIDED_180 * 5;
	if (player->pov >= (2 * PI))
		player->pov -= (float)(2 * PI);
	else if (player->pov <= 0)
		player->pov += (float)(2 * PI);
}

void		counting_player_coordinate(char *map, t_player *player, int length_line)
{
	int	count_line;
	int	x;
	int	y;

	y = 0;
	x = 0;
	count_line = 0;
	while (*map)
	{
		if (ft_strchr(PLAYER_POS, *map))
			player_coor_init(player, x, y, *map);
		if (++count_line == length_line)
		{
			y += 64;
			x = 0;
			count_line = 0;
		}
		else
			x += 64;
		map++;
	}
}

void		open_texture_files(t_map_data *map_data, void *mlx)
{
	t_img_data	*img;
	char 		q;

	q = 0;
	while (q < 4)
	{
		img = (t_img_data*)malloc(sizeof(t_img_data));
		map_data->textures_img[q] = img;
		img->img = mlx_xpm_file_to_image(mlx, map_data->textures[q], &img->img_width, &img->img_height);
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
		q++;
	}
}

t_img_data	*get_wall_color(const t_map_data *map_data, float ray_angle,
								  float dist_to_wall_h, float dist_to_wall_v)
{
	if (dist_to_wall_h > dist_to_wall_v)
	{
		if ((ray_angle < 2 / PI) || (ray_angle > 3 * PI / 2))
			return (map_data->textures_img[0]);
		else
			return (map_data->textures_img[1]);
	}
	else
	{
		if (ray_angle > PI)
			return (map_data->textures_img[2]);
		else
			return (map_data->textures_img[3]);
	}
}