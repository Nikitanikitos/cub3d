/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 19:24:50 by imicah            #+#    #+#             */
/*   Updated: 2020/06/13 19:24:52 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>

# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# define MAP_CHAR	" 012NSEW"
# define PLAYER_POS	"NSEW"

typedef struct		s_img_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int 			img_width;
	int 			img_height;
}					t_img_data;

typedef struct		s_wall_texture
{
	t_img_data		texture;
	float			step;
	int 			x;
	int 			y;
}					t_wall_texture;

typedef struct		s_player
{
	char			*map;
	float			position_x;
	float			position_y;
	float			pov;
}					t_player;

typedef struct		s_map_data
{
	t_img_data		textures[4];
	t_img_data		sprite_texture;
	t_wall_texture	wall_texture;
	t_img_data 		img_world;
	t_player		player;
	void			*mlx;
	void 			*win;
	char			*map;
	int 			resolution[2];
	int				length_line;
	char			floor_color[3];
	char			celling_color[3];
}					t_map_data;

char				get_map_data(char *line, t_map_data *map_data);
char				write_map(char fd, char *line, t_map_data *map_data);

int 				engine(t_map_data map_data);

void				exit_failure(char *error);

# endif
