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

#include <fcntl.h>

typedef struct s_desc
{
	int 		resolution_x;
	int 		resolution_y;
	char		*textures[4];
	char		*sprite_texture;
	char		*floor_color;
	char		*celling_color;
	char		*map;
}				t_descr;


