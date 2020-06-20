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


char	get_resolution(char *line, short *resolution)
{
	line += 2;
	if ((resolution[0] = (short)ft_atoi(line)) <= 0)
		return (-2);
	while ('0' <= *line && *line <= '9')
		line++;
	if ((resolution[1] = (short)ft_atoi(line)) <= 0)
		return (-2);
	return (1);
}

char	get_color(char *line, unsigned char *color)
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
				color[i++] = color_value;
			else
				return (-1);
		}
		else if (!(('0' <= *line && *line <= '9') || *line == '-'))
			flag = 1;
		line++;
	}
	return (1);
}

char 	get_desrc(char *line, t_descr **scene_descr)
{
	char	result;

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
		result = get_resolution(line, (*scene_descr)->resolution);
	else if (*line == 'F')
		result = get_color(line, (*scene_descr)->floor_color);
	else if (*line == 'C')
		result = get_color(line, (*scene_descr)->celling_color);
	else
		result = 0;
	free(line);
	return (result);
}

char 	*read_map(int fd, char **line)
{
	char			*map;
	char 			*temp_line;
	unsigned short	i;

	i = 0;
	map = NULL;
	while (get_next_line(fd, line) > 0)
	{
		if (**line)
		{
			map = ft_realloc(map, (int)ft_strlen(*line) + 2);
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
			map[i++] = '\n';
			map[i] = 0;
		}
		free(*line);
	}
	free(*line);
	return (map);
}

unsigned short	count_data(char *map_temp, unsigned short *lengh_line)
{
	unsigned short 	i;
	unsigned short	q;
	unsigned short	count_line;

	i = 0;
	*lengh_line = 0;
	count_line = 0;
	while (map_temp[i])
	{
		if ((q = (short)ft_strchr(map_temp + i, '\n')) > *lengh_line)
			*lengh_line = q - 1;
		count_line++;
		if (q == 0)
			return (--count_line);
		i += q;
	}
	return (count_line);
}

unsigned short	write_map(int fd, char **line, char **map)
{
	char	*map_temp;
	unsigned short	i;
	unsigned short	q;
	unsigned short	count_line;
	unsigned short	lengh_line;

	if ((map_temp = read_map(fd, line)) == NULL)
	{
		free(map_temp);
		return (0);
	}
	lengh_line = 0;
	i = 0;
	q = 0;
	count_line = count_data(map_temp, &lengh_line);
	*map = ft_calloc(sizeof(char), (lengh_line * count_line) + 1);
	count_line = 0;
	while (map_temp[i])
	{
		if (map_temp[i] == '\n')
		{
			while (count_line++ < lengh_line)
				(*map)[q++] = ' ';
			i++;
			count_line = 0;
		}
		(*map)[q++] = map_temp[i++];
		count_line++;
	}
	(*map)[q] = 0;
	free(map_temp);
	return (lengh_line);
}