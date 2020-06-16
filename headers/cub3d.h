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
# define MAP_CHAR " 012NSEW"

# include <fcntl.h>
# include "get_next_line.h"
# include "libft.h"
# include "mlx.h"

typedef struct			s_desc
{
	char				*map;
	char				*textures[4];
	char				*sprite_texture;
	short int 			resolution[2];
	short int			floor_color[3];
	short int			celling_color[3];
}						t_descr;

typedef struct 			s_player
{
	int 				direction_x;
	int 				direction_y;
	int 				position_x;
	int 				position_y;
}						s_player;

int		get_desrc(char *line, t_descr **scene_descr);
int 	engine(t_descr *scene_descr);

char	*get_map(int fd, char **line);

void	exit_failure(char *error, t_descr *scene_descr);
void	free_scene_descr(t_descr *scene_descr);

t_descr	*create_struct(void);

# endif