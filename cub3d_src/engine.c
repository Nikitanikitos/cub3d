/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 15:59:41 by imicah            #+#    #+#             */
/*   Updated: 2020/06/16 15:59:42 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void 	print_player(void *mlx, void * win, s_player *player);
int		key_win1(int key,s_player *p);

void print_wall(void *win, void *mlx, int pos_x, int pos_y)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x <= 32)
	{
		while (y <= 32)
			mlx_pixel_put(mlx,win, pos_x + x, pos_y + y++,02550);
		x++;
		y = 0;
	}
}

s_player *player_init(int pos_x, int pos_y, char direction)
{
	s_player	*player;

	if (!(player = (s_player*)malloc(sizeof(s_player))))
		return (NULL);
	player->position_x = pos_x + 16;
	player->position_y = pos_y + 16;
	if (direction == 'N' || direction == 'S')
		player->direction_x = 0;
	else if (direction == 'W' || direction == 'E')
		player->direction_y = 0;
	if (direction == 'N')
		player->direction_y = -1.0f;
	else if (direction == 'E')
		player->direction_x = 1.0f;
	else if (direction == 'S')
		player->direction_y = 1.0f;
	else
		player->direction_x = -1.0f;
	return (player);
}

int 	player_rotate(int key, s_player *player)
{
	if (key == 100)
		player->direction_y -= 0.1f;
	else if (key == 97)
		player->direction_y += 0.1f;

}

void 	print_player(void *mlx, void * win, s_player *player)
{
	int 	x;
	int		y;
	int 	q;

	x = 0;
	y = 0;
	q = 0;
	while (q++ <= 32)
	{
		mlx_pixel_put(mlx,win, player->position_x + x, player->position_y + y,123123);
		y += player->direction_y;
		x += player->direction_x;
	}
}

s_player 	*print_map(void *win, void *mlx, char *map)
{
	s_player	*player;
	int			pos_x;
	int			pos_y;

	pos_y = 0;
	pos_x = 0;
	player = NULL;
	while (*map)
	{
		if (*map == '1')
			print_wall(win, mlx, pos_x, pos_y);
		else if (ft_strchr("NWSE", *map))
		{
			player = player_init(pos_x, pos_y, *map);
			print_player(mlx, win, player);
		}
		if (*map++ == '\n')
		{
			pos_y += 32;
			pos_x = 0;
		}
		else
			pos_x += 32;
	}
	mlx_key_hook(win,key_win1,player);
	mlx_loop(mlx);
	return (player);
}

int	key_win1(int key,s_player *p)
{
	printf("Key in Win1 : %d\n",key);
	if (key==0xFF1B)
		exit(0);
}

int 	engine(t_descr *scene_descr)
{
	s_player	*player;
	void		*mlx;
	void 		*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, scene_descr->resolution[0], scene_descr->resolution[1], "Cub3D");
	player = print_map(win, mlx,scene_descr->map);
	return (0);
}