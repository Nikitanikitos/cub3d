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

# define MAP_CHAR	" 012NSEW"
# define PLAYER_POS	"NSEW"
# define KEY_W		119
# define KEY_S		115
# define KEY_D		100
# define KEY_A		97

# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

typedef struct			s_map_data
{
	char				*textures[4];
	char				*sprite_texture;
	short 				resolution[2];
	unsigned char		floor_color[3];
	unsigned char		celling_color[3];
	unsigned short		length_line;
	char				*map;
}						t_map_data;

typedef struct			s_player
{
	int 				direction_x;
	int 				direction_y;
	int 				position_x;
	int 				position_y;
	void				*mlx;
	void 				*win;
	char 				*map;
	unsigned short		length_line;
}						t_player;

typedef struct			s_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_data;

char					get_map_data(char *line, t_map_data **map_data);
int 					engine(t_map_data *map_data);

char					write_map(int fd, char **line, char **map, unsigned short *length_line);

void					exit_failure(char *error, t_map_data *map_data);
void					free_scene_descr(t_map_data *map_data);
void					free_player(t_player *player);

void					player_coor_init(t_player	*player, int pos_x, int pos_y, char direction);
t_player				*player_init(void *mlx, void *win, t_map_data *map_data);
t_map_data				*map_data_init(void);

# endif
