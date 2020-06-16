/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_descr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 16:48:25 by imicah            #+#    #+#             */
/*   Updated: 2020/06/15 16:48:26 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	get_resolution(char *line, short int *resolution)
{
	line += 2;
	if ((resolution[0] = (short)ft_atoi(line)) <= 0)
		resolution[0] = -1;
	while ('0' <= *line && *line <= '9')
		line++;
	if ((resolution[1] = (short)ft_atoi(line)) <= 0)
		resolution[0] = -1;
}

void	get_color(char *line, short int *color)
{
	int 	i;
	int 	color_value;
	int 	flag;

	i = 0;
	while (*line)
	{
		if ((('0' <= *line && *line <= '9') || *line == '-') && flag)
		{
			color_value = ft_atoi(line);
			flag = 0;
			if (0 <= color_value && color_value <= 255)
				color[i++] = (short)color_value;
			else
				color[i++] = -1;
		}
		else if (!(('0' <= *line && *line <= '9') || *line == '-'))
			flag = 1;
		line++;
	}
}

int 	get_desrc(char *line, t_descr **scene_descr)
{
	int 	result;

	result = 1;
	if (line[0] == 'N' && line[1] == 'O')
		(*scene_descr)->textures[0] = ft_strdup(line + 3);
	else if (line[0] == 'S' && line[1] == 'O')
		(*scene_descr)->textures[1] = ft_strdup(line + 3);
	else if (line[0] == 'W' && line[1] == 'E')
		(*scene_descr)->textures[2] = ft_strdup(line + 3);
	else if (line[0] == 'E' && line[1] == 'A')
		(*scene_descr)->textures[3] = ft_strdup(line + 3);
	else if (*line == 'S')
		(*scene_descr)->sprite_texture = ft_strdup(line + 2);
	else if (*line == 'R')
		get_resolution(line, (*scene_descr)->resolution);
	else if (*line == 'F')
		get_color(line, (*scene_descr)->floor_color);
	else if (*line == 'C')
		get_color(line, (*scene_descr)->celling_color);
	else
		result = 0;
	free(line);
	return (result);
}

char	*get_map(int fd, char **line)
{
	char	*map;
	char 	*temp_line;
	int 	i;

	i = 0;
	map = NULL;
	while (get_next_line(fd, line) > 0)
	{
		if (**line)
			map = ft_realloc(map, ft_strlen(*line) + 1);
		temp_line = *line;
		while (*temp_line)
		{
			if (ft_strchr(MAP_CHAR, *temp_line))
				map[i++] = *temp_line++;
			else
			{
				free(map);
				return (NULL);
			}
		}
		if (**line)
			map[i++] = '\n';
		free(*line);
	}
	free(*line);
	return (map);
}