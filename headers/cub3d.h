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

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

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

typedef struct		s_map
{
	char			*map;
	int				length_line;
	int				count_item;
}					t_map;

typedef struct		s_player
{
	t_map			map;
	float			position_x;
	float			position_y;
	float			pov;
}					t_player;

typedef struct		s_screen
{
	void			*mlx;
	void 			*win;
	t_img_data 		img_world;
	int 			resolution[2];
}					t_screen;

typedef struct		s_game_info
{
	t_img_data		textures[4];
	t_img_data		sprite_texture;
	t_map			map;
	t_color			floor_color;
	t_color			celling_color;
}					t_game_info;

typedef	struct		s_cub
{
	t_game_info		game_info;
	t_screen		screen;
	t_player		player;
	t_wall_texture	wall_texture;
}					t_cub;

char				get_map_data(char *line, t_game_info *game_info, t_screen *screen);
char				write_map(char fd, char *line, t_map *map);

int					engine(t_game_info game_info, t_screen screen, char *save);

void				exit_failure(char *error);

# endif
