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

typedef struct			s_desc
{
	int 				resolution[2];
	char				*textures[4];
	char				*sprite_texture;
	unsigned char		floor_color[3];
	unsigned char		celling_color[3];
	char				*map;
}						t_descr;

int		get_desrc(char *line, t_descr **scene_descr);
char	*get_map(int fd, char **line);

# endif