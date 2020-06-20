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

t_descr *descr_init(void)
{
	t_descr *scene_descr;

	if (!(scene_descr = (t_descr *)malloc(sizeof(t_descr))))
		return (NULL);
	ft_bzero(scene_descr->celling_color, 3);
	ft_bzero(scene_descr->floor_color, 3);
	ft_bzero(scene_descr->resolution, 2);
	scene_descr->map = NULL;
	scene_descr->textures[0] = NULL;
	scene_descr->textures[1] = NULL;
	scene_descr->textures[2] = NULL;
	scene_descr->textures[3] = NULL;
	scene_descr->sprite_texture = NULL;
	scene_descr->length_line = 0;
	return (scene_descr);
}

t_player *player_init(void *mlx, void *win, t_descr *scene_descr)
{
	t_player	*player;

	if (!(player = (t_player*)malloc(sizeof(t_player))))
		return (NULL);
	player->mlx = mlx;
	player->win = win;
	player->map = scene_descr->map;
	player->length_line = scene_descr->length_line;
	return (player);
}

t_player *player_coor_init(t_player	*player, int pos_x, int pos_y, char direction)
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