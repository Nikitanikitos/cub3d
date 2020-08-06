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

float	ray_casting(t_cub *cub, float ray_angle, int wall_x)
{
	const t_screen	screen = cub->screen;
	const t_player	player = cub->player;
	t_distance		dist_to_wall;
	float			height;
	float 			dist;

	dist_to_wall = calculate_distance_to_wall(cub, ray_angle);
	cub->wall_texture.x = (int)(CELL * dist_to_wall.x);
	height = calculate_height(dist_to_wall.distance, screen);
	dist = dist_to_wall.distance;
	dist_to_wall.distance = ((float)screen.height / 2 - height / 2) +
													player.crouch + player.look;
	rendering_floor(cub, (int)dist_to_wall.distance, wall_x);
	rendering_wall(cub, (int)dist_to_wall.distance, (int)height, wall_x);
	rendering_ceiling(cub, (int) (dist_to_wall.distance + height), wall_x);
	return (dist);
}

void	frame_rendering(t_cub *cub, t_player player, t_screen screen)
{
	const float	last_ray_angle = player.pov - (FOV_RAD / 2);
	const float	step = (FOV / (float)screen.width) * PI_DIV_180;
	float		ray_angle;
	float 		*distances;
	int			wall_x;

	wall_x = 0;
	ray_angle = player.pov + (FOV_RAD / 2);
	distances = (float*)malloc(sizeof(float) * screen.width);
	while (ray_angle >= last_ray_angle)
	{
		distances[wall_x] = ray_casting(cub, ray_angle, wall_x);
		ray_angle -= step;
		wall_x++;
	}
	rendering_sprites(cub->game_info, player, cub->screen, distances);
	free(distances);
	mlx_put_image_to_window(screen.mlx, screen.win, screen.img_world.img, 0, 0);
}

int		game_play(int key, t_cub *cub)
{
	if (key == ARROW_LEFT || key == ARROW_RIGHT ||
		key == ARROW_DOWN || key == ARROW_UP)
		change_pov(key, &cub->player);
	else if (key == XK_a || key == XK_d || key == XK_s || key == XK_w)
		change_position(key, &cub->player);
	else if (key == XK_Control_L)
		change_crouch(&cub->player);
	else if (key == XK_Escape)
		close_game(*cub);
	frame_rendering(cub, cub->player, cub->screen);
	return (0);
}

int		engine(t_game_info game_info, t_screen screen, char *save)
{
	t_cub	cub;

	cub = cub_init(screen, &game_info);
	screen = cub.screen;
	frame_rendering(&cub, cub.player, screen);
	if (!ft_strncmp(save, "--save", 6))
		save_bmp(screen.width, screen.height, screen.img_world.addr);
	else
	{
		mlx_hook(screen.win, 2, 1L << 0, game_play, &cub);
		mlx_hook(screen.win, 17, 1L << 17, close_game, &cub);
		mlx_loop(screen.mlx);
	}
	close_game(cub);
	return (0);
}
