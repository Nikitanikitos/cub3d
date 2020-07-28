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

#include "engine.h"

void	cast_ray_3d(t_generic *generic,
					float ray_angle, int wall_x)
{
	t_screen		screen = generic->screen;
	float			height;
	float			dist_to_wall;
	float			x;

	dist_to_wall = count_dist_to_wall(generic, ray_angle, &x);
	generic->wall_texture.x = ((int)(64 * x));
	height = 64 / dist_to_wall * ((float)screen.resolution[0] /
									2 / tanf(FOV_RAD / 2));
	dist_to_wall = (float)screen.resolution[1] / 2 - height / 2;
	drawing_floor(generic, (int)dist_to_wall, wall_x);
	drawing_wall(generic, (int)dist_to_wall, (int)height, wall_x);
	drawing_celling(generic, (int)(dist_to_wall + height), wall_x);
}

void	field_of_view_3d(t_generic *generic, t_player player, t_screen screen)
{
	const float	last_ray_angle = player.pov + (FOV_RAD / 2);
	const float	step = (FOV / (float)screen.resolution[0]) * PI_DIV_180;
	float		ray_angle;
	int			wall_x;

	ray_angle = player.pov - (FOV_RAD / 2);
	wall_x = 0;
	while (ray_angle <= last_ray_angle)
	{
		cast_ray_3d(generic, ray_angle, wall_x);
		ray_angle += step;
		wall_x++;
	}
	mlx_put_image_to_window(screen.mlx, screen.win, screen.img_world.img, 0, 0);
}

int		game_play(int key, t_generic *generic)
{
	if (key == KEY_E || key == KEY_Q)
		change_pov(key, &generic->player);
	else if (key == KEY_A || key == KEY_D || key == KEY_S || key == KEY_W)
		change_position(key, &generic->player);
	field_of_view_3d(generic, generic->player, generic->screen);
	return (0);
}

int		engine(t_game_info game_info, t_screen screen, char *save)
{
	t_generic	generic;
	t_player	player;

	player_init(&player, game_info.map);
	generic = generic_init(&screen, &player, &game_info);
	field_of_view_3d(&generic, player, screen);
	if (!ft_strncmp(save, "--save", 6))
		save_bmp(screen.resolution[0], screen.resolution[1],
					screen.img_world.addr);
	else
	{
		mlx_hook(screen.win, 2, 1L << 0, game_play, &generic);
		mlx_loop(screen.mlx);
	}
	return (0);
}
