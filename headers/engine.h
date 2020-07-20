/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:43:07 by imicah            #+#    #+#             */
/*   Updated: 2020/06/25 16:43:07 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "cub3d.h"
# include <math.h>

# define PI				3.14159265359
# define PI_DIVIDED_180	(float)(PI / 180)
# define FOV			60.f
# define FOV_RAD		FOV * PI_DIVIDED_180

# define KEY_W		119
# define KEY_S		115
# define KEY_D		100
# define KEY_A		97
# define KEY_Q		113
# define KEY_E		101

typedef struct		s_player
{
	float			position_x;
	float			position_y;
	float			pov;
	void			*mlx;
	void 			*win;
	t_map_data		*map_data;
}					t_player;

void				free_player(t_player *player);
void				player_coor_init(t_player *player, int pos_x, int pos_y, char direction);
t_player			*player_init(void *mlx, void *win, t_map_data *map_data);

void				counting_player_coordinate(char *map, t_player *player);
void				print_map(void *win, t_xvar *mlx, char *map, t_player *player);
void				change_position(int key, t_player *player);
void				change_pov(int key, t_player *player);
void				field_of_view(t_player *player, int color);

void				drawing_floor(t_player *player, short wall_x, float distance_to_wall);
void				drawing_celling(t_player *player, short wall_x, float wall_y);
float				drawing_wall(t_player *player, short wall_x, float wall_y, short height);


#endif
