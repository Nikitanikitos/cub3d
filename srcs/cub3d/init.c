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
	player->x = pos_x + 32;
	player->y = pos_y + 32;
	if (direction == 'E')
		player->pov = 0;
	else if (direction == 'N')
		player->pov = 90 * PI_DIV_180;
	else if (direction == 'W')
		player->pov = 180 * PI_DIV_180;
	else if (direction == 'S')
		player->pov = 270 * PI_DIV_180;
}

t_item	item_init(int x, int y)
{
	t_item	item;

	item.x = x - 32;
	item.y = y - 32;
	return (item);
}

void 	check(t_player *player, char c, int length_line, t_item *items)
{
	static int	count_line;
	static int 	i;
	static int	x;
	static int	y;

	if (c == '2')
		items[i++] = item_init(x, y);
	if (ft_strchr(PLAYER_POS, c))
		player_coor_init(player, x, y, c);
	else if (++count_line == length_line)
	{
		y += 64;
		x = 0;
		count_line = 0;
	}
	else
		x += 64;
}

t_player	player_init(t_game_info *game_info)
{
	t_map		map;
	t_player	player;
	t_item		*items;

	items = (t_item*)malloc(sizeof(t_item) * game_info->map.count_item);
	map = game_info->map;
	while (True)
	{
		if (!*map.map)
			break;
		check(&player, *map.map, map.length_line, items);
		map.map++;
	}
	player.map = game_info->map;
	game_info->items = items;
	return (player);
}

t_cub	cub_init(t_screen screen, t_game_info *game_info)
{
	t_player	player;
	t_cub		cub;
	t_img_data	img_world;

	player = player_init(game_info);
	screen.win = mlx_new_window(screen.mlx, screen.width,
									screen.height, "Cub3D");
	img_world.img = mlx_new_image(screen.mlx, screen.width, screen.height);
	img_world.addr = mlx_get_data_addr(img_world.img, &img_world.bpp,
									   &img_world.line_length, &img_world.endian);
	screen.img_world = img_world;
	cub.screen = screen;
	cub.player = player;
	cub.game_info = *game_info;
	return (cub);
}
