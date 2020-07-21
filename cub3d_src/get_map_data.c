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

char 	get_texture(char *line, char **texture)
{
	while (*line == ' ')
		line++;
	*texture = ft_strdup(line);
	if (open(*texture, O_RDONLY) == -1)
		return (-3);
	return (1);
}

char	get_resolution(char *line, short *resolution)
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

char	get_color(char *line, int *color)
{
	int 	color_value;
	int 	pow;
	int 	flag;
	int 	result;

	result = 0;
	pow = 65536;
	while (*line)
	{
		if ((('0' <= *line && *line <= '9') || *line == '-') && flag)
		{
			color_value = ft_atoi(line); // * 65536
			flag = 0;
			if (0 <= color_value && color_value <= 255)
			{
				result += color_value * pow;
				pow /= 256;
			}
			else
				return (-1);
		}
		else if (!(('0' <= *line && *line <= '9') || *line == '-'))
			flag = 1;
		line++;
	}
	*color = result;
	return (1);
}

char 	get_map_data(char *line, t_map_data **map_data)
{
	char	result;

	result = 0;
	if (line[0] == 'N' && line[1] == 'O')
		result = get_texture(line + 2, &(*map_data)->textures[0]);
	else if (line[0] == 'S' && line[1] == 'O')
		result = get_texture(line + 2, &(*map_data)->textures[1]);
	else if (line[0] == 'W' && line[1] == 'E')
		result = get_texture(line + 2, &(*map_data)->textures[2]);
	else if (line[0] == 'E' && line[1] == 'A')
		result = get_texture(line + 2, &(*map_data)->textures[3]);
	else if (*line == 'S')
		result = get_texture(line + 2, &(*map_data)->sprite_texture);
	else if (*line == 'R')
		result = get_resolution(line, (*map_data)->resolution);
	else if (*line == 'F')
		result = get_color(line, &(*map_data)->floor_color);
	else if (*line == 'C')
		result = get_color(line, &(*map_data)->celling_color);
	free(line);
	return (result);
}
