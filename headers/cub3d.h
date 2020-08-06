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
# include "bmp.h"
# include "mlx.h"
# include "mlx_int.h"

# define MAP_CHAR	" 012NSEW"
# define PLAYER_POS	"NSEW"

# define COLOR_ERR	-1
# define RES_ERR	-2
# define TEX_ERR	-3
# define COUNT_ARG	8

typedef struct		s_color
{
	u_int8_t		r;
	u_int8_t		g;
	u_int8_t		b;
}					t_color;

typedef struct		s_img_data
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int 			width;
	int 			height;
}					t_img_data;

typedef struct		s_texture
{
	t_img_data		img_data;
	float			step;
	int 			x;
	int 			y;
}					t_texture;

typedef struct		s_map
{
	char			*map;
	int				line_length;
	int 			column_length;
	int 			x;
	int 			y;
}					t_map;

typedef struct		s_player
{
	t_map			map;
	float			x;
	float			y;
	float			pov;
	float			crouch;
	float			look;
}					t_player;

typedef struct		s_screen
{
	void			*mlx;
	void 			*win;
	t_img_data 		img_world;
	int 			width;
	int 			height;
}					t_screen;

typedef struct		s_sprite
{
	float 			x;
	float			y;
	float			dist;
	int				h_offset;
	int				v_offset;
	int				height;
	t_texture		texture;
}					t_sprite;

typedef struct		s_game_info
{
	int				number_sprites;
	t_sprite		*sprites;
	t_img_data		textures[4];
	t_img_data		sprite_texture;
	t_map			map;
	t_color			floor_color;
	t_color			ceiling_color;
}					t_game_info;

typedef	struct		s_cub
{
	t_game_info		game_info;
	t_screen		screen;
	t_player		player;
	t_texture		wall_texture;
}					t_cub;

int8_t				get_data(char *line, t_game_info *game_info, t_screen *screen);
int8_t				read_map_data(char fd, t_game_info *game_info, t_map *map);
int8_t				check_valid_map(t_player player);

int					engine(t_game_info game_info, t_screen screen, char *save);

void				exit_failure(char *error);
int					close_game(t_cub cub);

# endif
