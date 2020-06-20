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

t_map_data	*map_data_init(void)
{
	t_map_data *map_data;

	if (!(map_data = (t_map_data*)malloc(sizeof(t_map_data))))
		return (NULL);
	ft_bzero(map_data->celling_color, 3);
	ft_bzero(map_data->floor_color, 3);
	ft_bzero(map_data->resolution, 2);
	map_data->map = NULL;
	map_data->textures[0] = NULL;
	map_data->textures[1] = NULL;
	map_data->textures[2] = NULL;
	map_data->textures[3] = NULL;
	map_data->sprite_texture = NULL;
	map_data->length_line = 0;
	return (map_data);
}

t_player	*player_init(void *mlx, void *win, t_map_data *map_data)
{
	t_player	*player;

	if (!(player = (t_player*)malloc(sizeof(t_player))))
		return (NULL);
	player->mlx = mlx;
	player->win = win;
	player->map = map_data->map;
	player->length_line = map_data->length_line;
	return (player);
}

void	player_coor_init(t_player	*player, int pos_x, int pos_y, char direction)
{
	player->position_x = pos_x + 16;
	player->position_y = pos_y + 16;
	if (direction == 'N' || direction == 'S')
		player->direction_x = 0;
	else if (direction == 'W' || direction == 'E')
		player->direction_y = 0;
	if (direction == 'N')
		player->direction_y = -1;
	else if (direction == 'E')
		player->direction_x = 1;
	else if (direction == 'S')
		player->direction_y = 1;
	else
		player->direction_x = -1;
}