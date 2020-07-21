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

typedef struct		s_texture_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int 			img_width;
	int 			img_height;
}					t_texture_data;

typedef struct		s_player
{
	char			*map;
	float			position_x;
	float			position_y;
	float			pov;
	void			*mlx;
	void 			*win;
}					t_player;

typedef struct			s_map_data
{
	char			*textures[4];
	t_texture_data	*textures_img[4];
	char			*sprite_texture;
	char			*map;
	int 			resolution[2];
	int				floor_color;
	int				celling_color;
	int				length_line;
	t_player		*player;
}					t_map_data;

char				get_map_data(char *line, t_map_data **map_data);
int 				engine(t_map_data *map_data);

char				write_map(char fd, char *line, t_map_data *map_data);

void				exit_failure(char *error, t_map_data *map_data);
void				free_scene_descr(t_map_data *map_data);

t_map_data			*map_data_init(void);

# endif
