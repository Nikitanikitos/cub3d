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


char	get_resolution(char *line, int 	*resolution)
{
	line += 2;
	if ((resolution[0] = ft_atoi(line)) <= 0)
		return (-1);
	while ('0' <= *line && *line <= '9')
		line++;
	if ((resolution[1] = ft_atoi(line)) <= 0)
		return (-1);
	return (1);
}

char	get_color(char *line, unsigned char *color)
{
	int 	i;
	int 	q;
	int 	flag;

	i = 0;
	while (*line)
	{
		if ((('0' <= *line && *line <= '9') || *line == '-') && flag)
		{
			q = ft_atoi(line);
			flag = 0;
			if (0 <= q && q <= 255)
				color[i++] = q;
			else
				return (-1);
		}
		else if (!(('0' <= *line && *line <= '9') || *line == '-'))
			flag = 1;
		line++;
	}
	return (1);
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
		result = get_color(line, (*scene_descr)->floor_color);
	else if (*line == 'C')
		result = get_color(line, (*scene_descr)->celling_color);
	else
		result = 0;
	if (result == -1)
		exit(EXIT_FAILURE);
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
			map = ft_realloc(map, ft_strlen(*line));
		temp_line = *line;
		while (*temp_line)
		{
			if (*temp_line == ' ' || *temp_line == '0' || *temp_line == '1' || *temp_line == '2' ||
				*temp_line == 'N' || *temp_line == 'S' || *temp_line == 'E' || *temp_line == 'W')
				map[i++] = *temp_line++;
			else
			{
				free(map);
				return (NULL);
			}
		}
		free(*line);
	}
	free(*line);
	return (map);
}