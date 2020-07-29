/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 19:08:46 by imicah            #+#    #+#             */
/*   Updated: 2020/06/20 19:08:47 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "engine.h"

void	player_coor_init(t_player *player, int pos_x, int pos_y, char direction)
{
	player->position_x = pos_x + 32;
	player->position_y = pos_y + 32;
	if (direction == 'E')
		player->pov = 0;
	else if (direction == 'N')
		player->pov = 90 * PI_DIV_180;
	else if (direction == 'W')
		player->pov = 180 * PI_DIV_180;
	else if (direction == 'S')
		player->pov = 270 * PI_DIV_180;
}

void	player_init(t_player *player, t_map map)
{
	int		count_line;
	int		x;
	int		y;

	y = 0;
	x = 0;
	count_line = 0;
	player->map = map;
	while (map.map)
	{
		if (ft_strchr(PLAYER_POS, *map.map))
		{
			player_coor_init(player, x, y, *map.map);
			break ;
		}
		else if (++count_line == map.length_line)
		{
			y += 64;
			x = 0;
			count_line = 0;
		}
		else
			x += 64;
		map.map++;
	}
}

t_cub	generic_init(t_screen *screen, t_player *player,
						  t_game_info *game_info)
{
	t_cub		cub;
	t_img_data	img_world;

	screen->win = mlx_new_window(screen->mlx, screen->width,
									screen->height, "Cub3D");
	img_world.img = mlx_new_image(screen->mlx, screen->width, screen->height);
	img_world.addr = mlx_get_data_addr(img_world.img, &img_world.bpp,
									   &img_world.line_length, &img_world.endian);
	screen->img_world = img_world;
	cub.screen = *screen;
	cub.player = *player;
	cub.game_info = *game_info;
	return (cub);
}
