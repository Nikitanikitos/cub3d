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

float	cast_ray(t_cub *cub, float ray_angle, int wall_x)
{
	const t_screen	screen = cub->screen;
	const t_player	player = cub->player;
	t_distance		dist_to_wall;
	float			height;
	float 			dist;

	dist_to_wall = count_dist_to_wall(cub, ray_angle);
	dist = dist_to_wall.distance;
	cub->wall_texture.x = (int)(CELL * dist_to_wall.x);
	height = count_height(dist_to_wall.distance, screen);
	dist_to_wall.distance = (float)(screen.height / 2 - height / 2) + player.crouch + player.look;
	drawing_floor(cub, (int)dist_to_wall.distance, wall_x);
	drawing_wall(cub, (int)dist_to_wall.distance, (int)height, wall_x);
	drawing_celling(cub, (int)(dist_to_wall.distance + height), wall_x);
	return (dist);
}

void	field_of_view(t_cub *cub, t_player player, t_screen screen)
{
	const float	last_ray_angle = player.pov - (FOV_RAD / 2);
	const float	step = (FOV / (float)screen.width) * PI_DIV_180;
	float		ray_angle;
	float 		*distances;
	int			wall_x;

	ray_angle = player.pov + (FOV_RAD / 2);
	wall_x = 0;
	distances = (float*)malloc(sizeof(float ) * screen.width);
	while (ray_angle >= last_ray_angle)
	{
		distances[wall_x] = cast_ray(cub, ray_angle, wall_x);
		ray_angle -= step;
		wall_x++;
	}
	drawing_items(cub->game_info, player, cub->screen, distances);
	free(distances);
	mlx_put_image_to_window(screen.mlx, screen.win, screen.img_world.img, 0, 0);
}

int		game_play(int key, t_cub *cub)
{
	if (key == ARROW_LEFT || key == ARROW_RIGHT ||
		key == ARROW_DOWN || key == ARROW_UP)
		change_pov(key, &cub->player);
	else if (key == XK_a || key == XK_d || key == XK_s || key == XK_w
		|| key == XK_Control_L)
		change_position(key, &cub->player);
	else if (key == XK_Escape)
		close_game(*cub);
	field_of_view(cub, cub->player, cub->screen);
	return (0);
}

int		engine(t_game_info game_info, t_screen screen, char *save)
{
	t_cub	cub;

	cub = cub_init(screen, &game_info);
	screen = cub.screen;
	field_of_view(&cub, cub.player, screen);
	if (!ft_strncmp(save, "--save", 6))
		save_bmp(screen.width, screen.height, screen.img_world.addr);
	else
	{
		mlx_hook(screen.win, 2, 1L << 0, game_play, &cub);
		mlx_loop(screen.mlx);
	}
	close_game(cub);
	return (0);
}
