/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 21:36:50 by imicah            #+#    #+#             */
/*   Updated: 2020/06/20 21:36:51 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char 	get_texture(char *line, t_img_data *img, void *mlx)
{
	while (*line == ' ')
		line++;
	if (open(line, O_RDONLY) == -1)
		return (-3);
	img->img = mlx_xpm_file_to_image(mlx, line, &img->img_width, &img->img_height);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_length, &img->endian);
//	img->img_current_width = 0;
	return (1);
}

char	get_resolution(char *line, int resolution[2])
{
	line += 2;
	if ((resolution[0] = (short)ft_atoi(line)) < 100)
		return (-2);
	while ('0' <= *line && *line <= '9')
		line++;
	if ((resolution[1] = (short)ft_atoi(line)) <= 100)
		return (-2);
	return (1);
}

char	get_color(char *line, char color[3])
{
	int 	color_value;
	int 	flag;
	int 	q;

	q = 0;
	while (*line)
	{
		if ((('0' <= *line && *line <= '9') || *line == '-') && flag)
		{
			color_value = ft_atoi(line);
			flag = 0;
			if (0 <= color_value && color_value <= 255)
			{
				color[q] = (char)color_value;
				q++;
			}
			else
				return (-1);
		}
		else if (!(('0' <= *line && *line <= '9') || *line == '-'))
			flag = 1;
		line++;
	}
	return (1);
}

char 	get_map_data(char *line, t_map_data *map_data)
{
	char	result;

	result = 0;
	if (line[0] == 'N' && line[1] == 'O')
		result = get_texture(line + 2, &(map_data)->textures[0], map_data->mlx);
	else if (line[0] == 'S' && line[1] == 'O')
		result = get_texture(line + 2, &(map_data)->textures[1], map_data->mlx);
	else if (line[0] == 'W' && line[1] == 'E')
		result = get_texture(line + 2, &(map_data)->textures[2], map_data->mlx);
	else if (line[0] == 'E' && line[1] == 'A')
		result = get_texture(line + 2, &(map_data)->textures[3], map_data->mlx);
	else if (*line == 'S')
		result = get_texture(line + 2, &(map_data)->sprite_texture, map_data->mlx);
	else if (*line == 'R')
		result = get_resolution(line, map_data->resolution);
	else if (*line == 'F')
		result = get_color(line, map_data->floor_color);
	else if (*line == 'C')
		result = get_color(line, map_data->celling_color);
	free(line);
	return (result);
}
